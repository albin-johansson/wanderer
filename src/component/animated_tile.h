#pragma once

#include <vector>

#include "types.h"

namespace wanderer {

struct Frame final {
  TileID tile{g_emptyTile};
  u32 duration{};
};

struct AnimatedTile final {
  u32 frame{0};
  std::vector<Frame> frames;
};

}  // namespace wanderer
