#include "tile_map_layer_impl.h"

#include <renderer.h>

#include "game_object.h"
#include "math.h"
#include "require.h"
#include "tile.h"
#include "tile_map_bounds.h"
#include "tile_set.h"
#include "viewport.h"

using namespace centurion;

namespace wanderer {

TileMapLayerImpl::TileMapLayerImpl(const SharedPtr<TileSet>& tileSet)
{
  this->m_tileSet = Require::not_null(tileSet);
}

TileMapLayerImpl::~TileMapLayerImpl() noexcept = default;

void TileMapLayerImpl::update(const TileMapBounds& bounds)
{
  for (auto row = bounds.minRow; row < bounds.maxRow; row++) {
    for (auto col = bounds.minCol; col < bounds.maxCol; col++) {
      const auto id = get_tile_id(row, col);
      if (id != Tile::empty) {
        m_tileSet->tick(id);
      }
    }
  }
}

TileID TileMapLayerImpl::get_tile_id(int row, int col) const
{
  try {
    return m_tiles.at(static_cast<std::size_t>(get_index(row, col)));
  } catch (...) {
    Log::critical("Failed to get tile ID of (%i, %i)!", row, col);
    throw;
  }
}

void TileMapLayerImpl::add_objects(const TileMapBounds& bounds,
                                   std::vector<IGameObject*>& objects)
{
  for (auto row = bounds.minRow; row < bounds.maxRow; row++) {
    for (auto col = bounds.minCol; col < bounds.maxCol; col++) {
      const auto pos = MapPosition{row, col};
      const auto iter = m_tileObjects.find(pos);
      if (iter != m_tileObjects.end()) {
        objects.push_back(iter->second.get());
      }
    }
  }
}

int TileMapLayerImpl::get_index(int row, int col) const noexcept
{
  return row * m_nCols + col;
}

bool TileMapLayerImpl::is_ground_layer() const noexcept
{
  return m_isGroundLayer;
}

int TileMapLayerImpl::get_rows() const noexcept
{
  return m_nRows;
}

int TileMapLayerImpl::get_cols() const noexcept
{
  return m_nCols;
}

}  // namespace wanderer
