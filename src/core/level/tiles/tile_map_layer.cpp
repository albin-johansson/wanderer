#include "tile_map_layer.h"
#include "tile.h"

namespace albinjohansson::wanderer {

TileMapLayer::TileMapLayer(int nRows, int nCols, std::vector<TileID> tiles)
    : nRows(nRows), nCols(nCols), tiles(std::move(tiles)) {}

TileMapLayer::~TileMapLayer() = default;

void TileMapLayer::Draw(Renderer& renderer,
                        RenderBounds bounds,
                        const Viewport& viewport,
                        const TileSet& tileSet) const {

  // TODO need to sort and draw entities as well
  for (auto row = bounds.minRow; row < bounds.maxRow; row++) {
    for (auto col = bounds.minCol; col < bounds.maxCol; col++) {
      TileID id = GetTileId(row, col);
      if (id == 0) {
        continue;
      }

      const TilePos pos = {row, col};
      const auto& tile = tileSet.GetTile(id);

      tile.Draw(pos, renderer, viewport, tileSet.GetSource(id));
    }
  }
}

TileID TileMapLayer::GetTileId(int row, int col) const {
  return tiles.at(GetIndex(row, col));
}

}
