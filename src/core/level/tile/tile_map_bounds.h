#pragma once

namespace wanderer {

struct TileMapBounds final {
  int minRow = 0;
  int maxRow = 0;
  int minCol = 0;
  int maxCol = 0;
};

}  // namespace wanderer