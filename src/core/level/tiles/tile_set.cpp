#include "tile_set.h"

namespace albinjohansson::wanderer {

TileSet::TileSet(int nTiles) {
  tiles.reserve(nTiles);
}

TileSet::~TileSet() = default;

void TileSet::tick(TileID id) {
  tiles.at(id).tick();
}

void TileSet::insert(TileID id, const Tile& tile) {
  tiles.emplace(id, tile);
}

const Tile& TileSet::get_tile(TileID id) const {
  return tiles.at(id);
}

}
