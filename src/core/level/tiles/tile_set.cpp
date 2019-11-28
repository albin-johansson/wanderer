#include "tile_set.h"

namespace albinjohansson::wanderer {

TileSet::TileSet(int nTiles) : nTiles(nTiles) {
  tiles.reserve(nTiles);
  for (int i = 0; i < nTiles; i++) {
    tiles.emplace_back((TileProperties) {nullptr, 0, false});
  }
}

TileSet::~TileSet() = default;

void TileSet::Tick(int index, ILevel& level) {
  tiles.at(index).Tick(level);
}

void TileSet::Insert(int index, const Tile& tile) {
  tiles.at(index) = tile;
}

}
