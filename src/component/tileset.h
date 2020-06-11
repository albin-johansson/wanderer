#pragma once

#include <vector>

#include "tile.h"

namespace wanderer {

struct Tileset final {
  // map TileID -> Tile
  std::vector<Tile> tiles;
};

}  // namespace wanderer
