#pragma once
#include "direction.h"

namespace wanderer {

struct Humanoid final {
};

struct HumanoidIdle final {
};

struct HumanoidMove final {
};

struct HumanoidAttack final {
  bool done{false};
};

struct HumanoidDie final {
};

}  // namespace wanderer
