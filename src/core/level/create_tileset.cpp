#include "create_tileset.hpp"

namespace wanderer {

auto create_tileset(const ir::tileset& data,
                    entt::registry& registry,
                    const comp::tileset::entity entity) -> comp::tileset&
{
  auto& tileset = registry.emplace<comp::tileset>(entity);
  tileset.tiles.reserve(data.tiles.size());

  for (const auto& [id, tileData] : data.tiles) {
    const auto tileEntity = comp::tile::entity{registry.create()};
    tileset.tiles.try_emplace(id, tileEntity);

    auto& tile = registry.emplace<comp::tile>(tileEntity);
    tile.id = id;
    tile.sheet = tileData.texture;
    tile.src = tileData.source;

    if (tileData.fancy) {
      const auto& fancy = *tileData.fancy;
      tile.depth = fancy.depth;

      if (fancy.animation) {
        registry.emplace<comp::animated_tile>(tileEntity, *fancy.animation);
      }
    }
  }

  return tileset;
}

}  // namespace wanderer
