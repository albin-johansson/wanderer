#include "tile_map.h"
#include "objects.h"

namespace albinjohansson::wanderer {

TileMap::TileMap(std::unique_ptr<TileSet> tileSet, int nRows, int nCols)
    : nRows(nRows), nCols(nCols) {
  this->tileSet = Objects::RequireNonNull(std::move(tileSet));
}

TileMap::~TileMap() = default;

TileMapBounds TileMap::CalculateMapBounds(const Rectangle& bounds) const noexcept {
  auto minCol = static_cast<int>(bounds.GetX() / Tile::SIZE);
  auto minRow = static_cast<int>(bounds.GetY() / Tile::SIZE);
  auto maxCol = static_cast<int>((bounds.GetMaxX() / Tile::SIZE) + 1);
  auto maxRow = static_cast<int>((bounds.GetMaxY() / Tile::SIZE) + 1);

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

void TileMap::Tick(const Viewport& viewport) {
  auto bounds = CalculateMapBounds(viewport.GetBounds());
  for (const auto& layer : layers) {
    layer->Update(bounds, *tileSet);
  }
}

void TileMap::Draw(Renderer& renderer, const Viewport& viewport) const noexcept {
  auto bounds = CalculateMapBounds(viewport.GetBounds());
  for (const auto& layer : layers) {
    layer->Draw(renderer, bounds, viewport, *tileSet);
  }
}

void TileMap::AddLayer(TileMapLayer_uptr layer) {
  layers.push_back(std::move(layer));
}

}