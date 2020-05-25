#pragma once
#include "types.h"

namespace wanderer {

struct GameLoop final {
  u64 then = 0;
  u64 now = 0;
  float delta = 0;
  float vsyncRate = 0;
  float timeStep = 0;
  float counterFreq = 0;
  float accumulator = 0;
  float deltaBuffer = 0;
};

}  // namespace wanderer
