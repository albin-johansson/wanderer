#pragma once

#include "direction.h"
#include "types.h"

namespace wanderer {

struct Humanoid final {
};

struct HumanoidIdle final {
};

struct HumanoidMove final {
};

struct HumanoidAttack final {
  entt::entity weapon{entt::null};
  bool done{false};
};

struct HumanoidDie final {
};

}  // namespace wanderer
