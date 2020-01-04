#include "tile_map_impl.h"
#include "tile_map_layer.h"
#include "tile_set.h"
#include "renderer.h"
#include "viewport.h"
#include "movable_object.h"
#include "entity.h"
#include "image.h"
#include "rectangle.h"
#include "wanderer_core.h"
#include "require.h"
#include "game_constants.h"
#include <algorithm>

namespace albinjohansson::wanderer {

TileMapImpl::TileMapImpl(const std::shared_ptr<TileSet>& tileSet) {
  this->tileSet = Require::NotNull(tileSet);
}

TileMapImpl::~TileMapImpl() = default;

void TileMapImpl::Interpolate(float alpha) {
  for (auto& entity : entityManager.GetCloseEntities()) {
    entity->interpolate(alpha);
  }
}

TileMapBounds TileMapImpl::CalculateMapBounds(const FRectangle& bounds) const noexcept {
  auto minCol = static_cast<int>(bounds.GetX()) / tileSizeInt;
  auto minRow = static_cast<int>(bounds.GetY()) / tileSizeInt;
  auto maxCol = static_cast<int>((bounds.GetMaxX()) / tileSizeInt) + 1;
  auto maxRow = static_cast<int>((bounds.GetMaxY()) / tileSizeInt) + 1;

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

void TileMapImpl::Tick(IWandererCore& core, const Viewport& viewport, float delta) {
  const auto& viewportBounds = viewport.GetBounds();
  const auto bounds = CalculateMapBounds(viewportBounds);
  const auto update = [&](auto& layer) { layer->Update(bounds); };

  std::for_each(groundLayers.begin(), groundLayers.end(), update);
  std::for_each(objectLayers.begin(), objectLayers.end(), update);

  entityManager.Update(viewportBounds);

  activeObjects.clear();

  for (const auto& layer : objectLayers) {
    layer->AddObjects(bounds, activeObjects);
  }

  for (const auto& entity : entityManager.GetCloseEntities()) {
    activeObjects.push_back(entity);
  }

  for (const auto& object : activeObjects) {
    object->tick(core, delta);
  }
}

void TileMapImpl::Draw(Renderer& renderer, const Viewport& viewport, float alpha) noexcept {
  Interpolate(alpha);

  const auto bounds = CalculateMapBounds(viewport.GetBounds());

  for (auto row = bounds.minRow; row < bounds.maxRow; row++) {
    for (auto col = bounds.minCol; col < bounds.maxCol; col++) {
      RenderTilesAt(row, col, renderer);
    }
  }

  const auto comparator = [&](const auto& fst, const auto& snd) noexcept {
    const auto leftFirst = fst->GetDepth();
    const auto leftSecond = fst->GetCenterY();

    const auto rightFirst = snd->GetDepth();
    const auto rightSecond = snd->GetCenterY();

    return (leftFirst < rightFirst || (rightFirst >= leftFirst && leftSecond < rightSecond));
  };

  std::sort(activeObjects.begin(), activeObjects.end(), comparator);

  for (const auto& object : activeObjects) {
    object->Draw(renderer, viewport);
  }
}

void TileMapImpl::RenderTilesAt(int row, int col, Renderer& renderer) {
  for (const auto& layer : groundLayers) {
    const auto id = layer->GetTileId(row, col);
    if (id != Tile::EMPTY) {
      Vector2 pos{static_cast<float>(col) * tileSize, static_cast<float>(row) * tileSize};
      tileSet->GetTile(id).Draw(pos, renderer, *tileSet);
    }
  }
}

void TileMapImpl::AddLayer(std::unique_ptr<ITileMapLayer>&& layer) {
  if (layer) {
    if (layer->IsGroundLayer()) {
      groundLayers.push_back(std::move(layer));
    } else {
      objectLayers.push_back(std::move(layer));
    }
  }
}

void TileMapImpl::SetPlayer(const std::shared_ptr<IEntity>& player) {
  if (player) {
    this->player = player;
    entityManager.AddEntity(player);
  }
}

bool TileMapImpl::IsBlocked(const IMovableObject* self, float delta) const {
  if (!self) {
    return false;
  }

  for (auto other : activeObjects) {
    if (other->get_unique_id() == self->get_unique_id()) {
      continue;
    }

    if (self->will_intersect(other, delta)) {
      return true;
    }
  }

  return false;
}

int TileMapImpl::GetRows() const noexcept {
  return nRows;
}

int TileMapImpl::GetCols() const noexcept {
  return nCols;
}

int TileMapImpl::GetWidth() const noexcept {
  return nCols * tileSizeInt;
}

int TileMapImpl::GetHeight() const noexcept {
  return nRows * tileSizeInt;
}

Vector2 TileMapImpl::GetPlayerSpawnPosition() const {
  return playerSpawnPos;
}

}