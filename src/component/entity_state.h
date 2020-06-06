#pragma once
#include "direction.h"

namespace wanderer {
// TODO rename

struct EntityIdleState {
};

struct EntityMoveState {
  Direction desiredDirection;  // TODO might be unnecessary
};

struct EntityAttackState {
};

struct EntityDieState {
};

}  // namespace wanderer
