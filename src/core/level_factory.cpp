#include "level_factory.hpp"

#include <entt.hpp>

#include "abby_utils.hpp"
#include "component/depth_drawable.hpp"
#include "depth_drawables_system.hpp"
#include "hitbox_system.hpp"
#include "humanoid_factory_system.hpp"
#include "make_map.hpp"
#include "make_registry.hpp"
#include "make_viewport.hpp"
#include "viewport_system.hpp"

namespace wanderer {

using tileset_entity = comp::tileset::entity;
using player_entity = comp::player::entity;

void level_factory::load_spawnpoint(level& level,
                                    const comp::spawnpoint& spawnpoint,
                                    cen::renderer& renderer,
                                    texture_cache& imageCache)
{
  // TODO think about how to copy player data between levels

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

void level_factory::init_tile_objects(entt::registry& registry,
                                      const comp::tilemap& tilemap,
                                      aabb_tree& aabbTree)
{
  for (const auto& [mapPos, tileObject] : tilemap.tileObjects) {
    const auto& drawable = registry.get<comp::depth_drawable>(tileObject.get());
    const auto& object = registry.get<comp::tile_object>(tileObject.get());
    if (const auto* hitbox = registry.try_get<comp::hitbox>(tileObject.get())) {
      const auto lower = abby_vector(hitbox->bounds.position());
      const auto upper = lower + abby_vector(hitbox->bounds.size());
      aabbTree.insert(tileObject.get(), lower, upper);
    }
  }
}

auto level_factory::make(const std::filesystem::path& path,
                         cen::renderer& renderer,
                         texture_cache& imageCache) -> level
{
  level level{make_registry()};
  level.m_aabbTree.set_thickness_factor(std::nullopt);

  auto& registry = level.registry();

  level.m_tilemap = make_map(registry, path, renderer, imageCache);

  assert(registry.view<comp::tileset>().size() == 1);
  level.m_tileset = tileset_entity{registry.view<comp::tileset>().front()};

  auto& tilemap = registry.get<comp::tilemap>(level.m_tilemap.get());
  level.m_viewport =
      sys::viewport::make_viewport(registry, {tilemap.width, tilemap.height});

  registry.view<comp::spawnpoint>().each(
      [&](const comp::spawnpoint& spawnpoint) {
        load_spawnpoint(level, spawnpoint, renderer, imageCache);
      });

  init_tile_objects(registry, tilemap, level.m_aabbTree);

  assert(level.m_playerSpawnPosition);
  sys::viewport::center_on(registry,
                           level.m_viewport,
                           level.player_spawnpoint());

  // This syncs the movable components with depth_drawable components
  sys::depthdrawable::update_movable(level.m_registry);

  return level;
}

}  // namespace wanderer
