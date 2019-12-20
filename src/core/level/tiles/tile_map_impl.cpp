#include "tile_map_impl.h"
#include "tile_map_layer.h"
#include "tile_map_bounds.h"
#include "tile_set.h"
#include "renderer.h"
#include "viewport.h"
#include "movable_object.h"
#include "entity.h"
#include "image.h"
#include "image_generator.h"
#include "rectangle.h"
#include "wanderer_core.h"
#include "objects.h"
#include "skeleton.h"
#include <algorithm>
#include <memory>
#include <vector>

namespace albinjohansson::wanderer {

TileMapImpl::TileMapImpl(const std::shared_ptr<TileSet>& tileSet,
                         int nRows,
                         int nCols,
                         ImageGenerator& imageGenerator)
    : nRows(nRows), nCols(nCols) {
  this->tileSet = Objects::RequireNonNull(tileSet);

  auto skeleton =
      std::make_shared<Skeleton>(imageGenerator.Load("resources/img/skeleton.png"));
  skeleton->SetSpeed(130);
  skeleton->SetX(1000);
  skeleton->SetY(500);

  entities.reserve(10);
  entities.push_back(skeleton);
}

TileMapImpl::~TileMapImpl() = default;

void TileMapImpl::Interpolate(float alpha) {
  for (auto& entity : entities) {
    entity->Interpolate(alpha);
  }
}

TileMapBounds TileMapImpl::CalculateMapBounds(const Rectangle& bounds) const noexcept {
  const int tileSize = Tile::SIZE;

  auto minCol = static_cast<int>(bounds.GetX()) / tileSize;
  auto minRow = static_cast<int>(bounds.GetY()) / tileSize;
  auto maxCol = static_cast<int>((bounds.GetMaxX()) / tileSize) + 1;
  auto maxRow = static_cast<int>((bounds.GetMaxY()) / tileSize) + 1;

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
  const auto viewportBounds = viewport.GetBounds();
  const auto bounds = CalculateMapBounds(viewportBounds);
  const auto update = [&](auto& layer) { layer->Update(bounds); };
  std::for_each(groundLayers.begin(), groundLayers.end(), update);
  std::for_each(objectLayers.begin(), objectLayers.end(), update);

  activeObjects.clear();

  for (const auto& layer : objectLayers) {
    layer->AddObjects(bounds, activeObjects);
  }

  for (const auto& entity : entities) {
    if (entity->GetHitbox().Intersects(viewportBounds)) {
      activeObjects.push_back(entity.get());
    }
  }

  for (const auto& object : activeObjects) {
    object->Tick(core, delta);
  }
}

void TileMapImpl::Draw(Renderer& renderer, const Viewport& viewport, float alpha) noexcept {
  Interpolate(alpha);

  const auto bounds = CalculateMapBounds(viewport.GetBounds());

  // Note! All loops takes constant time.
  for (auto row = bounds.minRow; row < bounds.maxRow; row++) {
    for (auto col = bounds.minCol; col < bounds.maxCol; col++) {
      for (const auto& layer : groundLayers) {
        const auto id = layer->GetTileId(row, col);
        if (id != Tile::EMPTY) {
          const auto& tile = tileSet->GetTile(id);
          tile.Draw(Vector2(col * Tile::SIZE, row * Tile::SIZE), renderer, viewport, *tileSet);
        }
      }
    }
  }

  const auto comparator = [&](const auto& fst, const auto& snd) noexcept {
    const auto leftFirst = fst->GetDepth();
    const auto leftSecond = fst->GetCenterY();

    const auto rightFirst = snd->GetDepth();
    const auto rightSecond = snd->GetCenterY();

    return (leftFirst < rightFirst || (!(rightFirst < leftFirst) && leftSecond < rightSecond));
  };

  std::sort(activeObjects.begin(), activeObjects.end(), comparator);

  for (const auto& object : activeObjects) {
    object->Draw(renderer, viewport);
  }
}

const auto comparator = [](const auto& fst, const auto& snd) noexcept {
  const auto leftFirst = fst->GetDepth();
  const auto leftSecond = fst->GetCenterY();

  const auto rightFirst = snd->GetDepth();
  const auto rightSecond = snd->GetCenterY();

  return (leftFirst < rightFirst || (!(rightFirst < leftFirst) && leftSecond < rightSecond));
};

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
    entities.push_back(player);
  }
}

bool TileMapImpl::IsBlocked(const IMovableObject* self, float delta) const {
  if (!self) {
    return false;
  }

  const auto& hitbox = self->GetHitbox();
  for (auto other : activeObjects) {
    if (other->GetUniqueID() == self->GetUniqueID()) {
      continue;
    }

    if (self->WillIntersect(other, delta)) {
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
  return nCols * Tile::SIZE_INT;
}

int TileMapImpl::GetHeight() const noexcept {
  return nRows * Tile::SIZE_INT;
}

Vector2 TileMapImpl::GetPlayerSpawnPosition() const {
  return Vector2(50, 50); // TODO
}

}