#pragma once
#include <vector>

#include "types.h"

namespace wanderer {

// A tag type for "ground" layers that are rendered first
struct GroundLayer final {
};

struct TileLayer final {
  using TileMatrix = std::vector<std::vector<entt::entity>>;

  TileMatrix matrix;
  int nRows;
  int nCols;
};

}  // namespace wanderer
