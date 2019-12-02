#include "tile_set.h"

namespace albinjohansson::wanderer {

TileSet::TileSet(int nTiles) {
  tiles.reserve(nTiles);

  // pasted from sprite_sheet.cpp
//  this->sheet = Objects::RequireNonNull(std::move(otherSheet));
//  nCols = static_cast<int>(sheet->GetWidth() / size);
//  nRows = static_cast<int>(sheet->GetHeight() / size);
//  nSprites = nRows * nCols;
//
//  TileID id = range.min;
//  for (int i = 0; i < nSprites; i++, id++) {
//    auto row = i / nCols;
//    auto col = i % nCols;
//    Rectangle rect(col * size, row * size, size, size);
//
//    sourceRectangles.insert(std::pair<TileID, Rectangle>(id, rect));
//  }
}

TileSet::~TileSet() = default;

void TileSet::Tick(TileID id) {
  try {
    tiles.at(id).Tick();
  } catch (std::exception& e) {
    SDL_Log("Invalid tile ID in tile set: %u (Tile set size: %llull)", id, tiles.size());
    throw;
  }
}

void TileSet::Insert(TileID id, const Tile& tile, const Rectangle& srcRect) {
  tiles.insert(std::pair<TileID, Tile>(id, tile));
  sourceRectangles.insert(std::pair<TileID, Rectangle>(id, srcRect));
}

const Rectangle& TileSet::GetSource(TileID id) const {
  return sourceRectangles.at(id);
}

}
