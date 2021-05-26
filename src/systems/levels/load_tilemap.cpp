#include "load_tilemap.hpp"

namespace wanderer::sys {

auto load_tilemap(entt::registry& registry,
                  const comp::tilemap::entity entity,
                  const ir::level& level) -> map_id
{
  auto& tilemap = registry.emplace<comp::tilemap>(entity);

  tilemap.id = map_id{level.id};
  tilemap.row_count = level.row_count;
  tilemap.col_count = level.col_count;
  tilemap.size = level.size;
  tilemap.humanoid_layer = level.humanoid_layer;

  return tilemap.id;
}

}  // namespace wanderer::sys
