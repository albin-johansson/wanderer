#include "tile_map_impl.h"

#include <rect.h>
#include <renderer.h>

#include <algorithm>

#include "entity.h"
#include "game_constants.h"
#include "movable_object.h"
#include "require.h"
#include "tile_map_layer.h"
#include "tile_set.h"
#include "viewport.h"
#include "wanderer_core.h"

using namespace centurion;

namespace wanderer {

TileMapImpl::TileMapImpl(const SharedPtr<TileSet>& tileSet)
{
  this->m_tileSet = Require::not_null(tileSet);
}

TileMapImpl::~TileMapImpl() = default;

void TileMapImpl::interpolate(float alpha)
{
  for (auto& entity : m_entityManager.get_close_entities()) {
    entity->interpolate(alpha);
  }
}

TileMapBounds TileMapImpl::calc_map_bounds(const FRect& bounds) const noexcept
{
  auto minCol = static_cast<int>(bounds.x()) / GameConstants::tile_size_int;
  auto minRow = static_cast<int>(bounds.y()) / GameConstants::tile_size_int;
  auto maxCol =
      static_cast<int>((bounds.max_x()) / GameConstants::tile_size_int) + 1;
  auto maxRow =
      static_cast<int>((bounds.max_y()) / GameConstants::tile_size_int) + 1;

  if (minCol < 0) {
    minCol = 0;
  }

  if (minRow < 0) {
    minRow = 0;
  }

  if (maxRow > m_nRows) {
    maxRow = m_nRows;
  }

  if (maxCol > m_nCols) {
    maxCol = m_nCols;
  }

  return {minRow, maxRow, minCol, maxCol};
}

void TileMapImpl::tick(IWandererCore& core,
                       const Viewport& viewport,
                       float delta)
{
  const auto& viewportBounds = viewport.get_bounds();
  const auto bounds = calc_map_bounds(viewportBounds);
  const auto update = [&](auto& layer) { layer->update(bounds); };

  std::for_each(m_groundLayers.begin(), m_groundLayers.end(), update);
  std::for_each(m_objectLayers.begin(), m_objectLayers.end(), update);

  m_entityManager.update(viewportBounds);

  m_activeObjects.clear();

  for (const auto& layer : m_objectLayers) {
    layer->add_objects(bounds, m_activeObjects);
  }

  for (const auto& entity : m_entityManager.get_close_entities()) {
    m_activeObjects.push_back(entity);
  }

  for (const auto& object : m_activeObjects) {
    object->tick(core, delta);
  }
}

void TileMapImpl::draw(Renderer& renderer,
                       const Viewport& viewport,
                       float alpha) noexcept
{
  interpolate(alpha);

  const auto bounds = calc_map_bounds(viewport.get_bounds());

  for (auto row = bounds.minRow; row < bounds.maxRow; row++) {
    for (auto col = bounds.minCol; col < bounds.maxCol; col++) {
      render_tiles_at(row, col, renderer);
    }
  }

  const auto comparator = [&](const auto& fst, const auto& snd) noexcept {
    const auto leftFirst = fst->get_depth();
    const auto leftSecond = fst->get_center_y();

    const auto rightFirst = snd->get_depth();
    const auto rightSecond = snd->get_center_y();

    return (leftFirst < rightFirst ||
            (rightFirst >= leftFirst && leftSecond < rightSecond));
  };

  std::sort(m_activeObjects.begin(), m_activeObjects.end(), comparator);

  for (const auto& object : m_activeObjects) {
    object->draw(renderer, viewport);
  }
}

void TileMapImpl::render_tiles_at(int row, int col, Renderer& renderer)
{
  for (const auto& layer : m_groundLayers) {
    const auto id = layer->get_tile_id(row, col);
    if (id != Tile::empty) {
      Vector2 pos{static_cast<float>(col) * GameConstants::tile_size,
                  static_cast<float>(row) * GameConstants::tile_size};
      m_tileSet->get_tile(id).draw(pos, renderer, *m_tileSet);
    }
  }
}

void TileMapImpl::add_layer(UniquePtr<ITileMapLayer>&& layer)
{
  if (layer) {
    if (layer->is_ground_layer()) {
      m_groundLayers.push_back(std::move(layer));
    } else {
      m_objectLayers.push_back(std::move(layer));
    }
  }
}

void TileMapImpl::set_player(const SharedPtr<IEntity>& player)
{
  if (player) {
    this->m_player = player;
    m_entityManager.add_entity(player);
  }
}

bool TileMapImpl::is_blocked(const IMovableObject* self, float delta) const
{
  if (!self) {
    return false;
  }

  for (const auto other : m_activeObjects) {
    if (other->get_unique_id() == self->get_unique_id()) {
      continue;
    }

    if (self->will_intersect(other, delta)) {
      return true;
    }
  }

  return false;
}

int TileMapImpl::get_rows() const noexcept
{
  return m_nRows;
}

int TileMapImpl::get_cols() const noexcept
{
  return m_nCols;
}

int TileMapImpl::get_width() const noexcept
{
  return m_nCols * GameConstants::tile_size_int;
}

int TileMapImpl::get_height() const noexcept
{
  return m_nRows * GameConstants::tile_size_int;
}

Vector2 TileMapImpl::get_player_spawn_position() const
{
  return m_playerSpawnPos;
}

}  // namespace wanderer