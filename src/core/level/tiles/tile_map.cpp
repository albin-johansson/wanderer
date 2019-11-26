#include "tile_map.h"
#include "objects.h"

namespace albinjohansson::wanderer {

TileMap::TileMap(std::unique_ptr<TileImageSet> tileImages, int nRows, int nCols)
    : nRows(nRows), nCols(nCols) {
  this->tileImages = Objects::RequireNonNull(std::move(tileImages));
}

TileMap::~TileMap() = default;

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
  auto bounds = CalculateRenderBounds(viewport.GetBounds());
  for (const auto& layer : layers) {
    layer->Draw(renderer, bounds, viewport, *tileImages);
  }
}

void TileMap::AddLayer(TileMapLayer_uptr layer) {
  layers.push_back(std::move(layer));
}

}