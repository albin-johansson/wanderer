#pragma once

#include "types.h"

namespace wanderer {

struct Animated final {
  u32 frame{0};
  u32 nFrames{1};
  u32 then{0};
  u32 delay{100};
};

}  // namespace wanderer
