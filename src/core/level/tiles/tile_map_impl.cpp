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

using namespace centurion;

namespace albinjohansson::wanderer {

TileMapImpl::TileMapImpl(const std::shared_ptr<TileSet>& tileSet) {
  this->tileSet = Require::not_null(tileSet);
}

TileMapImpl::~TileMapImpl() = default;

void TileMapImpl::Interpolate(float alpha) {
  for (auto& entity : entityManager.get_close_entities()) {
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

void TileMapImpl::tick(IWandererCore& core, const Viewport& viewport, float delta) {
  const auto& viewportBounds = viewport.get_bounds();
  const auto bounds = CalculateMapBounds(viewportBounds);
  const auto update = [&](auto& layer) { layer->update(bounds); };

  std::for_each(groundLayers.begin(), groundLayers.end(), update);
  std::for_each(objectLayers.begin(), objectLayers.end(), update);

  entityManager.update(viewportBounds);

  activeObjects.clear();

  for (const auto& layer : objectLayers) {
    layer->add_objects(bounds, activeObjects);
  }

  for (const auto& entity : entityManager.get_close_entities()) {
    activeObjects.push_back(entity);
  }

  for (const auto& object : activeObjects) {
    object->tick(core, delta);
  }
}

void TileMapImpl::draw(Renderer& renderer, const Viewport& viewport, float alpha) noexcept {
  Interpolate(alpha);

  const auto bounds = CalculateMapBounds(viewport.get_bounds());

  for (auto row = bounds.minRow; row < bounds.maxRow; row++) {
    for (auto col = bounds.minCol; col < bounds.maxCol; col++) {
      RenderTilesAt(row, col, renderer);
    }
  }

  const auto comparator = [&](const auto& fst, const auto& snd) noexcept {
    const auto leftFirst = fst->get_depth();
    const auto leftSecond = fst->get_center_y();

    const auto rightFirst = snd->get_depth();
    const auto rightSecond = snd->get_center_y();

    return (leftFirst < rightFirst || (rightFirst >= leftFirst && leftSecond < rightSecond));
  };

  std::sort(activeObjects.begin(), activeObjects.end(), comparator);

  for (const auto& object : activeObjects) {
    object->draw(renderer, viewport);
  }
}

void TileMapImpl::RenderTilesAt(int row, int col, Renderer& renderer) {
  for (const auto& layer : groundLayers) {
    const auto id = layer->get_tile_id(row, col);
    if (id != Tile::EMPTY) {
      Vector2 pos{static_cast<float>(col) * tileSize, static_cast<float>(row) * tileSize};
      tileSet->get_tile(id).draw(pos, renderer, *tileSet);
    }
  }
}

void TileMapImpl::add_layer(std::unique_ptr<ITileMapLayer>&& layer) {
  if (layer) {
    if (layer->is_ground_layer()) {
      groundLayers.push_back(std::move(layer));
    } else {
      objectLayers.push_back(std::move(layer));
    }
  }
}

void TileMapImpl::set_player(const std::shared_ptr<IEntity>& player) {
  if (player) {
    this->player = player;
    entityManager.add_entity(player);
  }
}

bool TileMapImpl::is_blocked(const IMovableObject* self, float delta) const {
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

int TileMapImpl::get_rows() const noexcept {
  return nRows;
}

int TileMapImpl::get_cols() const noexcept {
  return nCols;
}

int TileMapImpl::get_width() const noexcept {
  return nCols * tileSizeInt;
}

int TileMapImpl::get_height() const noexcept {
  return nRows * tileSizeInt;
}

Vector2 TileMapImpl::get_player_spawn_position() const {
  return playerSpawnPos;
}

}