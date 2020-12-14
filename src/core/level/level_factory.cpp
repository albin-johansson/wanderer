#include "level_factory.hpp"

#include <entt.hpp>

#include "centurion_utils.hpp"
#include "depth_drawable.hpp"
#include "depth_drawables_system.hpp"
#include "hitbox_system.hpp"
#include "humanoid_factory_system.hpp"
#include "make_registry.hpp"
#include "make_viewport.hpp"
#include "parse_map.hpp"
#include "portal.hpp"
#include "tile_object.hpp"
#include "viewport_system.hpp"

namespace wanderer {
namespace {

void insert_hitbox(aabb_tree& tree,
                   const entt::entity entity,
                   const comp::hitbox& hitbox)
{
  const auto lower = to_vector(hitbox.bounds.position());
  const auto upper = lower + to_vector(hitbox.bounds.size());
  tree.insert(entity, lower, upper);
}

}  // namespace

void level_factory::load_spawnpoint(level& level,
                                    const comp::spawnpoint& spawnpoint,
                                    graphics_context& graphics)
{
  const auto& tilemap = level.get<comp::tilemap>(level.tilemap());
  switch (spawnpoint.type) {
    case comp::spawnpoint_type::player: {
      const auto id = sys::humanoid::add_player(level.m_registry,
                                                level.m_aabbTree,
                                                spawnpoint.position,
                                                graphics);
      level.get<comp::depth_drawable>(id).layer = tilemap.humanoidLayer;
      level.m_player = comp::player::entity{id};
      level.m_playerSpawnPosition = spawnpoint.position;
      break;
    }
    case comp::spawnpoint_type::skeleton: {
      const auto id = sys::humanoid::add_skeleton(level.m_registry,
                                                  level.m_aabbTree,
                                                  spawnpoint.position,
                                                  graphics);
      level.get<comp::depth_drawable>(id).layer = tilemap.humanoidLayer;
      break;
    }
  }
}

void level_factory::setup_spawnpoints(level& level, graphics_context& graphics)
{
  level.each<comp::spawnpoint>([&](const comp::spawnpoint& spawnpoint) {
    load_spawnpoint(level, spawnpoint, graphics);
  });
}

void level_factory::setup_portals(level& level)
{
  level.each<comp::portal, comp::hitbox>([&](const entt::entity entity,
                                             const comp::portal&,
                                             const comp::hitbox& hitbox) {
    insert_hitbox(level.m_aabbTree, entity, hitbox);
  });
}

void level_factory::init_tile_objects(entt::registry& registry,
                                      const comp::tilemap& tilemap,
                                      aabb_tree& tree)
{
  const auto view = registry.view<comp::tile_object>();
  view.each([&](const entt::entity entity, const comp::tile_object&) {
    if (const auto* hitbox = registry.try_get<comp::hitbox>(entity)) {
      insert_hitbox(tree, entity, *hitbox);
    }
  });
}

auto level_factory::make(const std::filesystem::path& path,
                         graphics_context& graphics) -> std::unique_ptr<level>
{
  auto result = level::make(make_registry());
  auto& registry = result->registry();

  result->m_aabbTree.set_thickness_factor(std::nullopt);
  result->m_tilemap = parse_map(registry, path, graphics);

  assert(registry.view<comp::tileset>().size() == 1);
  result->m_tileset =
      comp::tileset::entity{registry.view<comp::tileset>().front()};

  auto& map = registry.get<comp::tilemap>(result->m_tilemap);
  result->m_viewport =
      sys::viewport::make_viewport(registry, {map.width, map.height});

  setup_spawnpoints(*result, graphics);
  init_tile_objects(registry, map, result->m_aabbTree);
  setup_portals(*result);

  assert(result->m_playerSpawnPosition);
  sys::viewport::center_on(registry,
                           result->m_viewport,
                           result->player_spawnpoint());

  // This syncs the movable components with depth_drawable components
  sys::depthdrawable::update_movable(result->m_registry);

  result->m_aabbTree.rebuild();

  return result;
}

}  // namespace wanderer
