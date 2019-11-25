#include "tile_map_layer.h"

namespace albinjohansson::wanderer {

TileMapLayer::TileMapLayer(int nRows, int nCols, std::vector<int>&& tiles)
    : nRows(nRows), nCols(nCols), tiles(tiles) {}

TileMapLayer::~TileMapLayer() = default;

void TileMapLayer::Draw(Renderer& renderer, RenderBounds bounds) const {
  for (int row = bounds.minRow; row < bounds.maxRow; row++) {
    for (int col = bounds.minCol; col < bounds.maxCol; col++) {

//      auto& tile = tileSet.GetTile(tiles->at(r).at(c));
//      tile.Draw({r, c}, renderer, viewport);

    }
  }
}

void TileMapLayer::SetTile(int row, int col, int id) {
  tiles.at(GetIndex(row, col)) = id;
}

int TileMapLayer::GetTile(int row, int col) const {
  return tiles.at(GetIndex(row, col));
}

}
