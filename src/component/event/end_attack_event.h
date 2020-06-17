#pragma once

#include "direction.h"
#include "types.h"

namespace wanderer {

struct EndAttackEvent final {
  entt::registry* registry{nullptr};
  entt::entity sourceEntity{entt::null};
  entt::entity weapon{entt::null};
  Direction direction{Direction::Down};
};

}  // namespace wanderer
