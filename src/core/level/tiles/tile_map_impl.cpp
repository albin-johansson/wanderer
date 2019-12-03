#include "tile_map_impl.h"
#include "objects.h"
#include "skeleton.h"
#include <algorithm>

namespace albinjohansson::wanderer {

TileMapImpl::TileMapImpl(std::unique_ptr<TileSet> tileSet,
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
  auto bounds = CalculateMapBounds(viewport.GetBounds());
  for (const auto& layer : layers) {
    layer->Update(bounds, *tileSet);
  }

  for (const auto& entity : entities) {
    entity->SavePosition();
    entity->Tick(core, delta);
  }
}

void TileMapImpl::Draw(Renderer& renderer, const Viewport& viewport, float alpha) noexcept {
  Interpolate(alpha);

  std::sort(entities.begin(), entities.end(), CompareGameObjects);

  auto bounds = CalculateMapBounds(viewport.GetBounds());

  // TODO use ground layers and sort the object layers
  for (const auto& layer : layers) {
    layer->Draw(renderer, bounds, viewport, *tileSet);
  }

  for (const auto& entity : entities) {
    entity->Draw(renderer, viewport);
  }
}

void TileMapImpl::AddLayer(ITileMapLayer_uptr layer) {
  layers.push_back(std::move(layer));
}

void TileMapImpl::SetPlayer(IEntity_sptr player) {
  if (player != nullptr) {
    this->player = player;
    entities.push_back(player);
  }
}

bool TileMapImpl::CompareGameObjects(const IGameObject_sptr& first,
                                     const IGameObject_sptr& second) noexcept {
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