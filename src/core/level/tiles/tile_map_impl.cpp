#include "tile_map_impl.h"
#include "objects.h"

namespace albinjohansson::wanderer {

TileMapImpl::TileMapImpl(std::unique_ptr<TileSet> tileSet, int nRows, int nCols)
    : nRows(nRows), nCols(nCols) {
  this->tileSet = Objects::RequireNonNull(std::move(tileSet));
}

TileMapImpl::~TileMapImpl() = default;

TileMapBounds TileMapImpl::CalculateMapBounds(const Rectangle& bounds) const noexcept {
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

void TileMapImpl::Tick(const Viewport& viewport) {
  auto bounds = CalculateMapBounds(viewport.GetBounds());
  for (const auto& layer : layers) {
    layer->Update(bounds, *tileSet);
  }
}

void TileMapImpl::Draw(Renderer& renderer, const Viewport& viewport) const noexcept {
  auto bounds = CalculateMapBounds(viewport.GetBounds());
  for (const auto& layer : layers) {
    layer->Draw(renderer, bounds, viewport, *tileSet);
  }
}

void TileMapImpl::AddLayer(ITileMapLayer_uptr layer) {
  layers.push_back(std::move(layer));
}

}