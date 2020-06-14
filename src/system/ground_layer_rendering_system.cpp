#include "ground_layer_rendering_system.h"

#include "animated_tile.h"
#include "render_bounds_system.h"
#include "tile.h"
#include "tile_layer.h"
#include "tile_rendering_system.h"
#include "tilemap.h"
#include "tileset.h"

using namespace centurion;

namespace wanderer::system::layer {

void render_ground(entt::registry& registry,
                   const entt::entity mapEntity,
                   Renderer& renderer,
                   const RenderBounds& bounds)
{
  const auto& tilemap = registry.get<Tilemap>(mapEntity);
  const auto& tileset = registry.get<Tileset>(tilemap.tileset);

  for (const auto layerEntity : tilemap.groundLayers) {
    const auto& tileLayer = registry.get<TileLayer>(layerEntity);

    for (auto row = bounds.minRow; row < bounds.maxRow; ++row) {
      for (auto col = bounds.minCol; col < bounds.maxCol; ++col) {
        const auto r = static_cast<std::size_t>(row);
        const auto c = static_cast<std::size_t>(col);

        const auto tileID = tileLayer.matrix.at(r).at(c);
        if (tileID == g_emptyTile) {
          continue;
        }

        const auto tileEntity = tileset.tiles.at(tileID);
        if (registry.has<AnimatedTile>(tileEntity)) {
          const auto& animatedTile = registry.get<AnimatedTile>(tileEntity);

          const auto id = animatedTile.frames.at(animatedTile.frame).tile;
          const auto animatedTileEntity = tileset.tiles.at(id);

          const auto& tile = registry.get<Tile>(animatedTileEntity);
          tile::render(renderer, tile, row, col);
        } else {
          const auto& tile = registry.get<Tile>(tileEntity);
          tile::render(renderer, tile, row, col);
        }
      }
    }
  }
}

}  // namespace wanderer::system::layer
