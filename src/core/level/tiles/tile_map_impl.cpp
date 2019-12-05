#include "tile_map_impl.h"
#include "objects.h"
#include "skeleton.h"
#include <algorithm>

namespace albinjohansson::wanderer {

TileMapImpl::TileMapImpl(TileSet_sptr tileSet, int nRows, int nCols, ImageGenerator& imageGenerator)
    : nRows(nRows), nCols(nCols) {
  this->tileSet = Objects::RequireNonNull(std::move(tileSet));

  auto skeleton =
      std::make_shared<Skeleton>(imageGenerator.Load("resources/img/skeleton.png"));
  skeleton->SetSpeed(130);
  skeleton->SetX(700);
  skeleton->SetY(500);

  entities.reserve(10);
  entities.push_back(skeleton);

  for (const auto& entity : entities) {
    drawables.push_back(entity);
  }
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
  auto bounds = CalculateMapBounds(viewport.GetBounds());

  for (const auto& layer : groundLayers) {
    layer->Update(bounds);
  }

  for (const auto& layer : objectLayers) {
    layer->Update(bounds);
  }

  for (const auto& entity : entities) {
    entity->SavePosition();
    entity->Tick(core, delta);
  }
}

void TileMapImpl::Draw(Renderer& renderer, const Viewport& viewport, float alpha) noexcept {
  Interpolate(alpha);

  const auto bounds = CalculateMapBounds(viewport.GetBounds());

  for (const auto& layer : groundLayers) {
    layer->Draw(renderer, bounds, viewport);
  }

  std::sort(drawables.begin(), drawables.end(), CompareDrawables);

  for (const auto& d : drawables) {
    d->Draw(renderer, viewport);
  }
}

void TileMapImpl::AddLayer(ITileMapLayer_uptr layer) {
  if (layer->IsGroundLayer()) {
    groundLayers.push_back(std::move(layer));
  } else {

    for (const auto& dt : layer->CreateDrawableTiles()) { // TODO TileObject class?
      drawables.push_back(dt);
    }

    objectLayers.push_back(std::move(layer));
  }
}

void TileMapImpl::SetPlayer(IEntity_sptr player) {
  if (player) {
    this->player = player;
    entities.push_back(player);
    drawables.push_back(player);
  }
}

bool TileMapImpl::CompareDrawables(const ISortableDrawable_sptr& first,
                                   const ISortableDrawable_sptr& second) noexcept {
  return first->GetY() < second->GetY();
}

Vector2 TileMapImpl::GetPlayerSpawnPosition() const {
  return Vector2(0, 0); // TODO
}

bool TileMapImpl::HasParent() const noexcept {
  auto p = parent.lock();
  return p != nullptr;
}

ITileMap_wptr TileMapImpl::GetParent() const noexcept {
  return parent;
}

void TileMapImpl::SetParent(ITileMap_wptr parent) {
  this->parent = parent;
}

}