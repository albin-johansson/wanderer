#include "tile_map.h"
#include "grass_tile.h"
#include "objects.h"

namespace albinjohansson::wanderer {

TileMap::TileMap(ImageGenerator& imageGenerator, int nRows, int nCols)
    : nRows(nRows), nCols(nCols), tileSet(imageGenerator) {
  tiles = std::make_unique<TileMatrix>();
  tiles->reserve(nRows);

  for (int row = 0; row < nRows; row++) {

    auto rowVector = std::vector<int>();
    rowVector.reserve(nCols);

    for (int col = 0; col < nCols; col++) {
      rowVector.push_back(0);
    }
    rowVector.shrink_to_fit();

    tiles->push_back(rowVector);
  }
  tiles->shrink_to_fit();
}

TileMap::~TileMap() = default;

TileMap_uptr TileMap::Create(ImageGenerator& imageGenerator, int nRows, int nCols) {
  return std::make_unique<TileMap>(imageGenerator, nRows, nCols);
}

RenderBounds TileMap::CalculateRenderBounds(const Rectangle& bounds) const noexcept {
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

  return {minRow, maxRow, minCol, maxCol};
}

void TileMap::Draw(Renderer& renderer, const Viewport& viewport) const noexcept {
  auto[minRow, maxRow, minCol, maxCol] = CalculateRenderBounds(viewport.GetBounds());

  for (int r = minRow; r < maxRow; r++) {
    for (int c = minCol; c < maxCol; c++) {
      auto& tile = tileSet.GetTile(tiles->at(r).at(c));
      tile.Draw({r, c}, renderer, viewport);
    }
  }
}

void TileMap::SetTile(int row, int col, int id) {
  tiles->at(row).at(col) = id;
}

}