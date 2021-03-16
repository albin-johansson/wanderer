#include "create_tilemap.hpp"

namespace wanderer {

auto create_tilemap(const ir::level& data,
                    entt::registry& registry,
                    const comp::tilemap::entity entity,
                    const comp::tileset::entity tileset) -> comp::tilemap&
{
  auto& tilemap = registry.emplace<comp::tilemap>(entity);

  tilemap.id = map_id{data.id};
  tilemap.rows = data.nRows;
  tilemap.cols = data.nCols;
  tilemap.tileset = tileset;
  tilemap.size = data.size;
  tilemap.humanoidLayer = data.humanoidLayer;

  return tilemap;
}

}  // namespace wanderer
