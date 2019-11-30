#include "tile_set.h"

namespace albinjohansson::wanderer {

TileSet::TileSet(int nTiles) : nTiles(nTiles) {
  tiles.reserve(nTiles);
}

TileSet::~TileSet() = default;

void TileSet::Tick(TileID id, ILevel& level) {
  tiles.at(id).Tick(level);
}

void TileSet::Insert(TileID id, const Tile& tile) {
  tiles.insert(std::pair<TileID, Tile>(id, tile));
}

}
