#include "tile_map.h"
#include "grass_tile.h"
#include "objects.h"

namespace albinjohansson::wanderer {

TileMap::TileMap(ImageGenerator& imageGenerator, int nRows, int nCols)
    : nRows(nRows), nCols(nCols) {
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

  tileSet.SetImage(0, imageGenerator.Load("resources/img/grass.png"));
}

TileMap::~TileMap() = default;

TileMap_uptr TileMap::Create(ImageGenerator& imageGenerator, int nRows, int nCols) {
  return std::make_unique<TileMap>(imageGenerator, nRows, nCols);
}

void TileMap::CalculateRenderBounds(const Rectangle& bounds,
                                    int& minRow,
                                    int& maxRow,
                                    int& minCol,
                                    int& maxCol) const noexcept {
  minCol = static_cast<int>(bounds.GetX() / ITile::SIZE);
  minRow = static_cast<int>(bounds.GetY() / ITile::SIZE);
  maxCol = static_cast<int>((bounds.GetMaxX() / ITile::SIZE) + 1);
  maxRow = static_cast<int>((bounds.GetMaxY() / ITile::SIZE) + 1);

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
}

void TileMap::Draw(Renderer& renderer, const Viewport& viewport) const noexcept {
  auto bounds = viewport.GetBounds();
  int minRow, maxRow, minCol, maxCol;
  CalculateRenderBounds(bounds, minRow, maxRow, minCol, maxCol);

  for (int r = minRow; r < maxRow; r++) {
    for (int c = minCol; c < maxCol; c++) {
      int id = tiles->at(r).at(c);
      Image_sptr image = tileSet.GetImage(id);
      if (image != nullptr) {
        auto x = viewport.GetTranslatedX(static_cast<float>(c) * ITile::SIZE);
        auto y = viewport.GetTranslatedY(static_cast<float>(r) * ITile::SIZE);
        renderer.RenderTexture(*image, x, y, ITile::SIZE, ITile::SIZE);
      }
    }
  }
}

void TileMap::SetTile(int row, int col, int id) {
  tiles->at(row).at(col) = id;
}

}