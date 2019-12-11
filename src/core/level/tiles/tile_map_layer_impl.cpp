#include "tile_map_layer_impl.h"
#include "tile.h"
#include "tile_set.h"
#include "tile_object.h"
#include "tile_map_bounds.h"
#include "sortable_drawable.h"
#include "renderer.h"
#include "viewport.h"
#include "objects.h"
#include <memory>
#include <map>

namespace albinjohansson::wanderer {

TileMapLayerImpl::TileMapLayerImpl(std::shared_ptr<TileSet> tileSet,
                                   int nRows,
                                   int nCols,
                                   std::vector<TileID> tiles)
    : nRows(nRows), nCols(nCols), tiles(std::move(tiles)) {
  this->tileSet = Objects::RequireNonNull(std::move(tileSet));
  InitTileObjects();
}

TileMapLayerImpl::~TileMapLayerImpl() noexcept = default;

void TileMapLayerImpl::InitTileObjects() {
  int index = 0;
  for (const auto id : tiles) {
    if (id != Tile::EMPTY && tileSet->GetTile(id).IsObject()) {
      auto object = std::make_shared<TileObject>(id, CreatePosition(index), tileSet);
      object->SetDepth(tileSet->GetTile(id).GetDepth());
      tileObjects.emplace(index, object);
    }
    ++index;
  }
}

Vector2 TileMapLayerImpl::CreatePosition(int index) const {
  const auto mapPosition = GetPosition(index);
  return Vector2(mapPosition.col * Tile::SIZE, mapPosition.row * Tile::SIZE);
}

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

void TileMapLayerImpl::DrawTile(Renderer& renderer,
                                const MapPosition& position,
                                const Viewport& viewport) const {
  const auto id = GetTileId(position.row, position.col);
  if (id != Tile::EMPTY) {
    const Vector2 pos = {static_cast<float>(position.col) * Tile::SIZE,
                         static_cast<float>(position.row) * Tile::SIZE};
    tileSet->GetTile(id).Draw(pos, renderer, viewport, *tileSet);
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
                                  std::vector<std::shared_ptr<ISortableDrawable>>& drawables) {
  for (auto row = bounds.minRow; row < bounds.maxRow; row++) {
    for (auto col = bounds.minCol; col < bounds.maxCol; col++) {
      const auto index = GetIndex(row, col);
      if (tileObjects.count(index)) {
        drawables.push_back(tileObjects.at(index));
      }
    }
  }
}

const std::vector<TileID>& TileMapLayerImpl::GetTiles() const noexcept {
  return tiles;
}

MapPosition TileMapLayerImpl::GetPosition(int index) const noexcept {
  return {index / nCols, index % nCols};
}

int TileMapLayerImpl::GetIndex(int row, int col) const noexcept {
  return row * nCols + col;
}

bool TileMapLayerImpl::IsGroundLayer() const noexcept {
  return isGroundLayer;
}

}