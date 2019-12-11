#include "tile_map_impl.h"
#include "tile_map_layer.h"
#include "tile_map_bounds.h"
#include "tile_set.h"
#include "renderer.h"
#include "viewport.h"
#include "entity.h"
#include "image_generator.h"
#include "rectangle.h"
#include "wanderer_core.h"
#include "objects.h"
#include "skeleton.h"
#include <algorithm>
#include <memory>
#include <vector>

namespace albinjohansson::wanderer {

TileMapImpl::TileMapImpl(std::shared_ptr<TileSet> tileSet,
                         int nRows,
                         int nCols,
                         ImageGenerator& imageGenerator)
    : nRows(nRows), nCols(nCols) {
  this->tileSet = Objects::RequireNonNull(std::move(tileSet));

  auto skeleton =
      std::make_shared<Skeleton>(imageGenerator.Load("resources/img/skeleton.png"));
  skeleton->SetSpeed(130);
  skeleton->SetX(700);
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

void TileMapImpl::Tick(IWandererCore& core, const Viewport& viewport, float delta) {
  const auto viewportBounds = viewport.GetBounds();
  const auto bounds = CalculateMapBounds(viewportBounds);
  const auto update = [&](auto& layer) { layer->Update(bounds); };
  std::for_each(groundLayers.begin(), groundLayers.end(), update);
  std::for_each(objectLayers.begin(), objectLayers.end(), update);

  drawables.clear();

  for (const auto& entity : entities) {
    if (viewportBounds.Intersects(entity->GetHitbox())) {
      entity->SavePosition(); // FIXME should probably be automatic
      entity->Tick(core, delta);

      drawables.push_back(entity);
    }
  }

  for (const auto& layer : objectLayers) {
    layer->AddObjects(bounds, drawables);
  }
}

void TileMapImpl::Draw(Renderer& renderer, const Viewport& viewport, float alpha) noexcept {
  Interpolate(alpha);

  const auto bounds = CalculateMapBounds(viewport.GetBounds());

  // Note! All loops takes constant time.
  for (auto row = bounds.minRow; row < bounds.maxRow; row++) {
    for (auto col = bounds.minCol; col < bounds.maxCol; col++) {

      auto drawTile = [&](const auto& layer) {
        const auto id = layer->GetTileId(row, col);
        if (id != Tile::EMPTY) {
          const auto& tile = tileSet->GetTile(id);
          tile.Draw(Vector2(col * Tile::SIZE, row * Tile::SIZE), renderer, viewport, *tileSet);
        }
      };

      std::for_each(groundLayers.begin(), groundLayers.end(), drawTile);
    }
  }

  auto comparator = [&](const auto& fst, const auto& snd) noexcept {
    const auto leftFirst = fst->GetDepth();
    const auto leftSecond = fst->GetCenterY();

    const auto rightFirst = snd->GetDepth();
    const auto rightSecond = snd->GetCenterY();

    return (leftFirst < rightFirst || (!(rightFirst < leftFirst) && leftSecond < rightSecond));
  };

  std::sort(drawables.begin(), drawables.end(), comparator);

  for (const auto& drawable : drawables) {
    drawable->Draw(renderer, viewport);
  }
}

void TileMapImpl::AddLayer(std::unique_ptr<ITileMapLayer> layer) {
  if (layer) {
    if (layer->IsGroundLayer()) {
      groundLayers.push_back(std::move(layer));
    } else {
      objectLayers.push_back(std::move(layer));
    }
  }
}

void TileMapImpl::SetPlayer(std::shared_ptr<IEntity> player) {
  if (player) {
    this->player = player;
    entities.push_back(player);
  }
}

std::weak_ptr<ITileMap> TileMapImpl::GetParent() const noexcept {
  return parent;
}

void TileMapImpl::SetParent(std::weak_ptr<ITileMap> parent) {
  this->parent = parent;
}

int TileMapImpl::GetRows() const noexcept {
  return nRows;
}

int TileMapImpl::GetCols() const noexcept {
  return nCols;
}

int TileMapImpl::GetWidth() const noexcept {
  return nCols * static_cast<int>(Tile::SIZE);
}

int TileMapImpl::GetHeight() const noexcept {
  return nRows * static_cast<int>(Tile::SIZE);
}

bool TileMapImpl::HasParent() const noexcept {
  auto p = parent.lock();
  return p != nullptr;
}

Vector2 TileMapImpl::GetPlayerSpawnPosition() const {
  return Vector2(0, 0); // TODO
}

}