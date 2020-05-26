#pragma once
#include "direction.h"

namespace wanderer {

struct EntityIdleState {
};

struct EntityMoveState {
  Direction desiredDirection;
};

struct EntityAttackState {
};

struct EntityDieState {
};

}  // namespace wanderer
