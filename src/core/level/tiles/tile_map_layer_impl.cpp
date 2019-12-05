#include "tile_map_layer_impl.h"
#include "tile.h"
#include "objects.h"

namespace albinjohansson::wanderer {

TileMapLayerImpl::TileMapLayerImpl(TileSet_sptr tileSet,
                                   int nRows,
                                   int nCols,
                                   std::vector<TileID> tiles)
    : nRows(nRows), nCols(nCols), tiles(std::move(tiles)) {
  this->tileSet = Objects::RequireNonNull(std::move(tileSet));
}

TileMapLayerImpl::~TileMapLayerImpl() = default;

void TileMapLayerImpl::Update(const TileMapBounds& bounds) {
  for (auto row = bounds.minRow; row < bounds.maxRow; row++) {
    for (auto col = bounds.minCol; col < bounds.maxCol; col++) {
      TileID id = GetTileId(row, col);
      if (id == 0) {
        continue;
      }
      tileSet->Tick(id);
    }
  }
}

void TileMapLayerImpl::Draw(Renderer& renderer,
                            const TileMapBounds& bounds,
                            const Viewport& viewport) const {
  for (auto row = bounds.minRow; row < bounds.maxRow; row++) {
    for (auto col = bounds.minCol; col < bounds.maxCol; col++) {
      // FIXME duplicated rendering code from DrawableTile

      TileID id = GetTileId(row, col);
      if (id == Tile::EMPTY) {
        continue;
      }

      const TilePos pos = {row, col};
      const auto& tile = tileSet->GetTile(id);

      TileID frameId = tile.GetFrameId();

      tile.Draw(pos, renderer, viewport, tileSet->GetSource(frameId));
    }
  }
}

TileID TileMapLayerImpl::GetTileId(int row, int col) const {
  return tiles.at(GetIndex(row, col));
}

void TileMapLayerImpl::SetGroundLayer(bool isGroundLayer) noexcept {
  this->isGroundLayer = isGroundLayer;
}

std::vector<DrawableTile_sptr> TileMapLayerImpl::CreateDrawableTiles() const {
  std::vector<DrawableTile_sptr> drawables;

  auto i = 0;
  for (const auto& tileId : tiles) {
    if (tileId != Tile::EMPTY) {
      auto x = static_cast<float>(i % nCols) * Tile::SIZE;
      auto y = (static_cast<float>(i) / static_cast<float>(nCols)) * Tile::SIZE;

      drawables.push_back(std::make_unique<DrawableTile>(x, y, tileId, tileSet));
    }
    ++i;
  }

  return drawables;
}

}
