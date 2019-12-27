#include "tile_map_layer_impl.h"
#include "tile.h"
#include "tile_set.h"
#include "tile_object.h"
#include "tile_map_bounds.h"
#include "sortable_drawable.h"
#include "game_object.h"
#include "renderer.h"
#include "viewport.h"
#include "require.h"
#include "math_utils.h"
#include <memory>

namespace albinjohansson::wanderer {

TileMapLayerImpl::TileMapLayerImpl(const std::shared_ptr<TileSet>& tileSet,
                                   int nRows,
                                   int nCols,
                                   std::vector<TileID>&& tiles)
    : nRows(nRows), nCols(nCols), tiles(tiles) {
  this->tileSet = Require::NotNull(tileSet);
  InitTileObjects();
}

TileMapLayerImpl::~TileMapLayerImpl() noexcept = default;

void TileMapLayerImpl::InitTileObjects() {
  int index = 0;
  for (const auto id : tiles) {
    if (id != Tile::EMPTY) {
      const auto& tile = tileSet->GetTile(id);
      if (tile.IsObject()) {
        auto object = std::make_shared<TileObject>(id, CreatePosition(index), tileSet);
        object->SetDepth(tile.GetDepth());

        if (tile.IsBlocked()) {
          Hitbox hitbox = tile.GetHitbox();

          hitbox.SetX(object->GetX());
          hitbox.SetY(object->GetY());

          object->SetHitbox(hitbox);
        }

        const auto matrixPos = MathUtils::IndexToMatrixPos(index, nCols);
        MapPosition mapPos = {matrixPos.first, matrixPos.second};

        tileObjects.emplace(mapPos, object);
      }
    }
    ++index;
  }
}

Vector2 TileMapLayerImpl::CreatePosition(int index) const {
  const auto pos = MathUtils::IndexToMatrixPos(index, nCols);
  return Vector2(pos.second * Tile::SIZE, pos.first * Tile::SIZE);
}

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

void TileMapLayerImpl::SetGroundLayer(bool isGroundLayer) noexcept {
  this->isGroundLayer = isGroundLayer;
}

void TileMapLayerImpl::AddObjects(const TileMapBounds& bounds,
                                  std::vector<IGameObject*>& objects) {
  for (auto row = bounds.minRow; row < bounds.maxRow; row++) {
    for (auto col = bounds.minCol; col < bounds.maxCol; col++) {
      const MapPosition pos = {row, col};
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

}
