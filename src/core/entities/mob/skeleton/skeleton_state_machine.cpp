#include "skeleton_state_machine.h"
#include "skeleton_idle_state.h"
#include "skeleton_moving_state.h"
#include "skeleton_attack_state.h"

namespace wanderer::core {

SkeletonStateMachine::SkeletonStateMachine(IEntity* entity)
    : AbstractEntityStateMachine(entity) {

  // TODO add different states
  Put(EntityStateID::IDLE, std::make_unique<SkeletonIdleState>(this));
  Put(EntityStateID::WALK, std::make_unique<SkeletonMovingState>(this));
  Put(EntityStateID::ATTACK, std::make_unique<SkeletonAttackState>(this));
}

SkeletonStateMachine::~SkeletonStateMachine() = default;

}
