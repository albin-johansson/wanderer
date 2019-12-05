#include "tile_set.h"

namespace albinjohansson::wanderer {

TileSet::TileSet(int nTiles) {
  tiles.reserve(nTiles);
}

TileSet::~TileSet() = default;

void TileSet::Tick(TileID id) {
  tiles.at(id).Tick();
}

void TileSet::Insert(TileID id, const Tile& tile, const Rectangle& srcRect) {
  tiles.insert(std::pair<TileID, Tile>(id, tile));
  sourceRectangles.insert(std::pair<TileID, Rectangle>(id, srcRect));
}

const Rectangle& TileSet::GetSource(TileID id) const {
  return sourceRectangles.at(id);
}

const Tile& TileSet::GetTile(TileID id) const {
  return tiles.at(id);
}

}
