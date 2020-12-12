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

using tileset_entity = comp::tileset::entity;
using player_entity = comp::player::entity;

void level_factory::load_spawnpoint(level& level,
                                    const comp::spawnpoint& spawnpoint,
                                    cen::renderer& renderer,
                                    texture_cache& cache)
{
  const auto& tilemap = level.get<comp::tilemap>(level.tilemap());
  switch (spawnpoint.type) {
    case comp::spawnpoint_type::player: {
      const auto id = sys::humanoid::add_player(level.m_registry,
                                                level.m_aabbTree,
                                                spawnpoint.position,
                                                renderer,
                                                cache);
      level.get<comp::depth_drawable>(id).layer = tilemap.humanoidLayer;
      level.m_player = player_entity{id};
      level.m_playerSpawnPosition = spawnpoint.position;
      break;
    }
    case comp::spawnpoint_type::skeleton: {
      const auto id = sys::humanoid::add_skeleton(level.m_registry,
                                                  level.m_aabbTree,
                                                  spawnpoint.position,
                                                  renderer,
                                                  cache);
      level.get<comp::depth_drawable>(id).layer = tilemap.humanoidLayer;
      break;
    }
  }
}

void level_factory::setup_spawnpoints(level& level,
                                      cen::renderer& renderer,
                                      texture_cache& cache)
{
  level.each<comp::spawnpoint>([&](const comp::spawnpoint& spawnpoint) {
    load_spawnpoint(level, spawnpoint, renderer, cache);
  });
}

void level_factory::setup_portals(level& level)
{
  level.each<comp::portal, comp::hitbox>([&](const entt::entity entity,
                                             const comp::portal&,
                                             const comp::hitbox& hitbox) {
    const auto lower = to_vector(hitbox.bounds.position());
    const auto upper = lower + to_vector(hitbox.bounds.size());
    level.m_aabbTree.insert(entity, lower, upper);
  });
}

void level_factory::init_tile_objects(entt::registry& registry,
                                      const comp::tilemap& tilemap,
                                      aabb_tree& aabbTree)
{
  registry.view<comp::tile_object>().each(
      [&](const entt::entity e, const comp::tile_object&) {
        if (const auto* hitbox = registry.try_get<comp::hitbox>(e)) {
          const auto lower = to_vector(hitbox->bounds.position());
          const auto upper = lower + to_vector(hitbox->bounds.size());
          aabbTree.insert(e, lower, upper);
        }
      });
}

auto level_factory::make(const std::filesystem::path& path,
                         cen::renderer& renderer,
                         texture_cache& cache) -> std::unique_ptr<level>
{
  auto result = level::make(make_registry());
  auto& registry = result->registry();

  result->m_aabbTree.set_thickness_factor(std::nullopt);
  result->m_tilemap = parse_map(registry, path, renderer, cache);

  assert(registry.view<comp::tileset>().size() == 1);
  result->m_tileset = tileset_entity{registry.view<comp::tileset>().front()};

  auto& tilemap = registry.get<comp::tilemap>(result->m_tilemap);

  {
    const cen::farea levelSize{tilemap.width, tilemap.height};
    result->m_viewport = sys::viewport::make_viewport(registry, levelSize);
  }

  setup_spawnpoints(*result, renderer, cache);
  init_tile_objects(registry, tilemap, result->m_aabbTree);
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
