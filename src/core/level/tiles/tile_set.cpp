#include "tile_set.h"

namespace albinjohansson::wanderer {

TileSet::TileSet(int nTiles) : nTiles(nTiles) {
  tiles.reserve(nTiles);
}

TileSet::~TileSet() = default;

void TileSet::Tick(TileID index, ILevel& level) {
  tiles.at(index).Tick(level);
}

void TileSet::Insert(TileID index, const Tile& tile) {
  tiles.insert(std::pair<TileID, Tile>(index, tile));
}

}
