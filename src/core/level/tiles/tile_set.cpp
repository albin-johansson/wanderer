#include "tile_set.h"

namespace albinjohansson::wanderer {

TileSet::TileSet(int nTiles) : nTiles(nTiles) {
  tiles.reserve(nTiles);
}

TileSet::~TileSet() = default;

void TileSet::Tick(int index, ILevel& level) {
  tiles.at(index).Tick(level);
}

void TileSet::Insert(int index, const Tile& tile) {
  tiles.insert(std::pair<int, Tile>(index, tile));
}

}
