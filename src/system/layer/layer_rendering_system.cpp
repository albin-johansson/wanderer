#include "layer_rendering_system.h"

#include "animated_tile.h"
#include "tile_rendering_system.h"

using namespace wanderer::component;

namespace wanderer::system::layer {

void render(entt::registry& registry,
            const TileLayer& layer,
            ctn::Renderer& renderer,
            const Tileset& tileset,
            const RenderBounds& bounds)
{
  for (auto row = bounds.minRow; row < bounds.maxRow; ++row) {
    for (auto col = bounds.minCol; col < bounds.maxCol; ++col) {
      const auto r = static_cast<std::size_t>(row);
      const auto c = static_cast<std::size_t>(col);

      const TileID id = layer.matrix.at(r).at(c);
      if (id == g_emptyTile) {
        continue;
      }

      const Tile::entity entity = tileset.tiles.at(id);

      if (registry.has<AnimatedTile>(entity.get())) {
        const auto& tile = tile::animated_tile(registry, entity, tileset);
        tile::render(renderer, tile, row, col);
      } else {
        const auto& tile = registry.get<Tile>(entity.get());
        tile::render(renderer, tile, row, col);
      }
    }
  }
}

}  // namespace wanderer::system::layer
