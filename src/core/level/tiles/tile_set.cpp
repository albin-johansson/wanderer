#include "tile_set.h"

namespace albinjohansson::wanderer {

TileSet::TileSet(int nTiles) {
  tiles.reserve(nTiles);
}

TileSet::~TileSet() = default;

void TileSet::Tick(TileID id) {
  tiles.at(id).tick();
}

void TileSet::Insert(TileID id, const Tile& tile) {
  tiles.emplace(id, tile);
}

const Tile& TileSet::GetTile(TileID id) const {
  return tiles.at(id);
}

}
