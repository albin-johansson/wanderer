#include "tile_set.h"

namespace albinjohansson::wanderer {

TileSet::TileSet(int nTiles) {
  tiles.reserve(nTiles);
}

TileSet::~TileSet() = default;

void TileSet::Tick(TileID id) {
  try {
    tiles.at(id).Tick();
  } catch (std::exception& e) {
    SDL_Log("Failed to tick tile %u!", id);
    throw;
  }
}

void TileSet::Insert(TileID id, const Tile& tile, const Rectangle& srcRect) {
  tiles.insert(std::pair<TileID, Tile>(id, tile));
  sourceRectangles.insert(std::pair<TileID, Rectangle>(id, srcRect));
}

const Rectangle& TileSet::GetSource(TileID id) const {
  try {
    return sourceRectangles.at(id);
  } catch (std::exception& e) {
    SDL_Log("Failed get source rectangle for: %u", id);
    throw;
  }
}

}
