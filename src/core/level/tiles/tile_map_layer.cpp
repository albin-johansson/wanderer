#include "tile_map_layer.h"
#include "tile.h"

namespace albinjohansson::wanderer {

TileMapLayer::TileMapLayer(int nRows, int nCols, std::vector<int> tiles)
    : nRows(nRows), nCols(nCols), tiles(std::move(tiles)) {}

TileMapLayer::~TileMapLayer() = default;

void TileMapLayer::Draw(Renderer& renderer,
                        RenderBounds bounds,
                        const Viewport& viewport,
                        const TileImageSet& images) const {

  // TODO need to sort and draw entities as well
  for (auto row = bounds.minRow; row < bounds.maxRow; row++) {
    for (auto col = bounds.minCol; col < bounds.maxCol; col++) {
      int tileId = GetTile(row, col);

      if (tileId == 0) {
        continue;
      }

      Rectangle src = images.GetSource(tileId);
      Rectangle dst = {viewport.GetTranslatedX(col * Tile::SIZE),
                       viewport.GetTranslatedY(row * Tile::SIZE),
                       Tile::SIZE,
                       Tile::SIZE};

      renderer.RenderTexture(*images.GetImage(tileId), src, dst);
    }
  }
}

int TileMapLayer::GetTile(int row, int col) const {
  return tiles.at(GetIndex(row, col));
}

}
