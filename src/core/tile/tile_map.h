#pragma once
#include "tile.h"
#include <vector>
#include <memory>

namespace wanderer::core {

//using TileMatrix_uptr = std::unique_ptr<std::vector<std::vector<Tile>>>;

class TileMap final {
 private:
//  TileMatrix_uptr tiles = nullptr;

 public:
  TileMap(int nRows, int nCols);

  ~TileMap();
};

}
