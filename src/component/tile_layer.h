#pragma once
#include <vector>

#include "types.h"

namespace wanderer {

struct TileLayer final {
  using TileMatrix = std::vector<std::vector<TileID>>;

  TileMatrix matrix;
  int nRows;
  int nCols;
};

}  // namespace wanderer
