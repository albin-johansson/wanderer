#include "load_tilemap.hpp"

namespace wanderer::sys {

auto LoadTilemap(entt::registry& registry,
                 const entt::entity entity,
                 const ir::level& level) -> MapID
{
  auto& tilemap = registry.emplace<comp::Tilemap>(entity);

  tilemap.id = MapID{level.id};
  tilemap.row_count = level.row_count;
  tilemap.col_count = level.col_count;
  tilemap.size = level.size;
  tilemap.humanoid_layer = level.humanoid_layer;

  return tilemap.id;
}

}  // namespace wanderer::sys
