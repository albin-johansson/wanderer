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
#include "viewport_system.hpp"

namespace wanderer {

using tileset_entity = comp::tileset::entity;
using player_entity = comp::player::entity;

void level_factory::load_spawnpoint(level& level,
                                    const comp::spawnpoint& spawnpoint,
                                    cen::renderer& renderer,
                                    texture_cache& imageCache)
{
  switch (spawnpoint.type) {
    case comp::spawnpoint_type::player: {
      const auto id = sys::humanoid::add_player(level.m_registry,
                                                level.m_aabbTree,
                                                spawnpoint.position,
                                                renderer,
                                                imageCache);
      level.m_player = player_entity{id};
      level.m_playerSpawnPosition = spawnpoint.position;
      break;
    }
    case comp::spawnpoint_type::skeleton: {
      sys::humanoid::add_skeleton(level.m_registry,
                                  level.m_aabbTree,
                                  spawnpoint.position,
                                  renderer,
                                  imageCache);
      break;
    }
  }
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
  for (const auto& [mapPos, tileObject] : tilemap.tileObjects) {
    const auto& drawable = registry.get<comp::depth_drawable>(tileObject);
    const auto& object = registry.get<comp::tile_object>(tileObject);
    if (const auto* hitbox = registry.try_get<comp::hitbox>(tileObject)) {
      const auto lower = to_vector(hitbox->bounds.position());
      const auto upper = lower + to_vector(hitbox->bounds.size());
      aabbTree.insert(tileObject, lower, upper);
    }
  }
}

auto level_factory::make(const std::filesystem::path& path,
                         cen::renderer& renderer,
                         texture_cache& imageCache) -> std::unique_ptr<level>
{
  auto lvl = level::make(make_registry());
  lvl->m_aabbTree.set_thickness_factor(std::nullopt);

  auto& registry = lvl->registry();

  lvl->m_tilemap = parse_map(registry, path, renderer, imageCache);

  assert(registry.view<comp::tileset>().size() == 1);
  lvl->m_tileset = tileset_entity{registry.view<comp::tileset>().front()};

  auto& tilemap = registry.get<comp::tilemap>(lvl->m_tilemap);
  lvl->m_viewport =
      sys::viewport::make_viewport(registry, {tilemap.width, tilemap.height});

  registry.view<comp::spawnpoint>().each(
      [&](const comp::spawnpoint& spawnpoint) {
        load_spawnpoint(*lvl, spawnpoint, renderer, imageCache);
      });

  init_tile_objects(registry, tilemap, lvl->m_aabbTree);
  setup_portals(*lvl);

  assert(lvl->m_playerSpawnPosition);
  sys::viewport::center_on(registry, lvl->m_viewport, lvl->player_spawnpoint());

  // This syncs the movable components with depth_drawable components
  sys::depthdrawable::update_movable(lvl->m_registry);

  return lvl;
}

}  // namespace wanderer
