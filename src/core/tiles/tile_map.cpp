#include "tile_map.h"
#include "grass_tile.h"

namespace wanderer::core {

TileMap::TileMap(int nRows, int nCols) : nRows(nRows), nCols(nCols) {
  tiles = std::make_unique<TileMatrix>();
  tiles->reserve(nRows);

  for (int row = 0; row < nRows; row++) {

    auto rowVector = std::vector<ITile_sptr>();
    rowVector.reserve(nCols);

    for (int col = 0; col < nCols; col++) {
      rowVector.push_back(std::make_shared<GrassTile>(row, col, 0));
    }

    tiles->push_back(rowVector);
  }
}

TileMap::~TileMap() = default;

void TileMap::Draw(visuals::Renderer& renderer, const Viewport& viewport) const noexcept {
  auto tiles = GetTiles(viewport.GetBounds());
  for (ITile_sptr tile : tiles) {
    tile->Draw(renderer, viewport);
  }
}

std::vector<ITile_sptr> TileMap::GetTiles(const Rectangle& bounds) const { // TODO shouldn't be const
  auto minCol = static_cast<int>(bounds.GetX() / ITile::SIZE);
  auto minRow = static_cast<int>(bounds.GetY() / ITile::SIZE);
  auto maxCol = static_cast<int>((bounds.GetMaxX() / ITile::SIZE) + 1);
  auto maxRow = static_cast<int>((bounds.GetMaxY() / ITile::SIZE) + 1);

  if (minCol < 0) {
    minCol = 0;
  }

  if (minRow < 0) {
    minRow = 0;
  }

  if (maxRow > nRows) {
    maxRow = nRows;
  }

  if (maxCol > nCols) {
    maxCol = nCols;
  }

  int size = (maxCol - minCol) * (maxRow - minRow);
  auto result = std::vector<ITile_sptr>();
  result.reserve(size);

  for (int row = minRow; row < maxRow; row++) {
    for (int col = minCol; col < maxCol; col++) {
      result.push_back(tiles->at(row).at(col));
    }
  }

  return result;
}

}