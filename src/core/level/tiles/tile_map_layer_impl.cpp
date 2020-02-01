#include "tile_map_layer_impl.h"
#include <renderer.h>
#include "tile.h"
#include "tile_set.h"
#include "tile_map_bounds.h"
#include "game_object.h"
#include "viewport.h"
#include "require.h"
#include "math.h"

namespace albinjohansson::wanderer {

TileMapLayerImpl::TileMapLayerImpl(const std::shared_ptr<TileSet>& tileSet) {
  this->tileSet = Require::not_null(tileSet);
}

TileMapLayerImpl::~TileMapLayerImpl() noexcept = default;

void TileMapLayerImpl::update(const TileMapBounds& bounds) {
  for (auto row = bounds.minRow; row < bounds.maxRow; row++) {
    for (auto col = bounds.minCol; col < bounds.maxCol; col++) {
      const auto id = get_tile_id(row, col);
      if (id != Tile::EMPTY) {
        tileSet->tick(id);
      }
    }
  }
}

TileID TileMapLayerImpl::get_tile_id(int row, int col) const {
  try {
    return tiles.at(static_cast<std::size_t>(get_index(row, col)));
  } catch (std::exception& e) {
    SDL_Log("Failed to get tile ID of tile at (%i, %i)", row, col);
    throw;
  }
}

void TileMapLayerImpl::add_objects(const TileMapBounds& bounds,
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

int TileMapLayerImpl::get_index(int row, int col) const noexcept {
  return row * nCols + col;
}

bool TileMapLayerImpl::is_ground_layer() const noexcept {
  return isGroundLayer;
}

int TileMapLayerImpl::get_rows() const noexcept {
  return nRows;
}

int TileMapLayerImpl::get_cols() const noexcept {
  return nCols;
}

}
