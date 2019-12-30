#include "tile_map_layer_impl.h"
#include "tile.h"
#include "tile_set.h"
#include "tile_object.h"
#include "tile_map_bounds.h"
#include "game_object.h"
#include "renderer.h"
#include "viewport.h"
#include "require.h"
#include "math_utils.h"
#include <memory>

namespace albinjohansson::wanderer {

TileMapLayerImpl::TileMapLayerImpl(const std::shared_ptr<TileSet>& tileSet) {
  this->tileSet = Require::NotNull(tileSet);
}

TileMapLayerImpl::~TileMapLayerImpl() noexcept = default;

void TileMapLayerImpl::Update(const TileMapBounds& bounds) {
  for (auto row = bounds.minRow; row < bounds.maxRow; row++) {
    for (auto col = bounds.minCol; col < bounds.maxCol; col++) {
      const auto id = GetTileId(row, col);
      if (id != Tile::EMPTY) {
        tileSet->Tick(id);
      }
    }
  }
}

TileID TileMapLayerImpl::GetTileId(int row, int col) const {
  try {
    return tiles.at(GetIndex(row, col));
  } catch (std::exception& e) {
    SDL_Log("Failed to get tile ID of tile at (%i, %i)", row, col);
    throw;
  }
}

void TileMapLayerImpl::AddObjects(const TileMapBounds& bounds,
                                  std::vector<IGameObject*>& objects) {
  for (auto row = bounds.minRow; row < bounds.maxRow; row++) {
    for (auto col = bounds.minCol; col < bounds.maxCol; col++) {
      const auto pos = MapPosition{row, col};
      const auto iter = tileObjects.find(pos);
      if (iter != tileObjects.end()) {
        objects.push_back(iter->second.get());
      }
    }
  }
}

int TileMapLayerImpl::GetIndex(int row, int col) const noexcept {
  return row * nCols + col;
}

bool TileMapLayerImpl::IsGroundLayer() const noexcept {
  return isGroundLayer;
}

int TileMapLayerImpl::GetRows() const noexcept {
  return nRows;
}

int TileMapLayerImpl::GetCols() const noexcept {
  return nCols;
}

}
