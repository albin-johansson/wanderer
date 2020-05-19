#include "tile_set.h"

namespace wanderer {

TileSet::TileSet(int nTiles)
{
  m_tiles.reserve(nTiles);
}

TileSet::~TileSet() = default;

void TileSet::tick(TileID id)
{
  m_tiles.at(id).tick();
}

void TileSet::insert(TileID id, const Tile& tile)
{
  m_tiles.emplace(id, tile);
}

const Tile& TileSet::get_tile(TileID id) const
{
  return m_tiles.at(id);
}

}  // namespace wanderer
