#include "ground_layer_rendering_system.h"

#include "animated_tile.h"
#include "game_constants.h"
#include "render_bounds_system.h"
#include "tile.h"
#include "tile_layer.h"
#include "tilemap.h"
#include "tileset.h"
#include "viewport.h"

using namespace centurion;

namespace wanderer {

namespace {

void render_tile(Renderer& renderer,
                 const Tile& tile,
                 const int row,
                 const int col) noexcept
{
  const auto x = static_cast<float>(col) * g_tileSize<float>;
  const auto y = static_cast<float>(row) * g_tileSize<float>;
  const FRect dst{{x, y}, {g_tileSize<float>, g_tileSize<float>}};

  renderer.render_tf(*tile.sheet, tile.src, dst);
}

}  // namespace

void render_ground_layers(entt::registry& registry,
                          const entt::entity mapEntity,
                          const entt::entity viewportEntity,
                          Renderer& renderer)
{
  const auto& tilemap = registry.get<Tilemap>(mapEntity);
  const auto& tileset = registry.get<Tileset>(tilemap.tileset);

  const auto renderBounds = calculate_render_bounds(
      registry, viewportEntity, tilemap.rows, tilemap.cols);

  for (const auto layerEntity : tilemap.groundLayers) {
    const auto& tileLayer = registry.get<TileLayer>(layerEntity);

    for (auto row = renderBounds.minRow; row < renderBounds.maxRow; ++row) {
      for (auto col = renderBounds.minCol; col < renderBounds.maxCol; ++col) {

        const auto r = static_cast<std::size_t>(row);
        const auto c = static_cast<std::size_t>(col);
        const auto tileID = tileLayer.matrix.at(r).at(c);

        if (tileID != g_emptyTile) {
          const auto tileEntity = tileset.tiles.at(tileID);
          if (registry.has<AnimatedTile>(tileEntity)) {
            const auto& animatedTile = registry.get<AnimatedTile>(tileEntity);

            const auto id = animatedTile.frames.at(animatedTile.frame).tile;
            const auto animatedTileEntity = tileset.tiles.at(id);

            const auto& tile = registry.get<Tile>(animatedTileEntity);
            render_tile(renderer, tile, row, col);
          } else {
            const auto& tile = registry.get<Tile>(tileEntity);
            render_tile(renderer, tile, row, col);
          }
        }
      }
    }
  }
}

}  // namespace wanderer
