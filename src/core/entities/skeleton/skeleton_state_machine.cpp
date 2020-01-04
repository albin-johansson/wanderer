#include "skeleton_state_machine.h"
#include "skeleton_idle_state.h"
#include "skeleton_moving_state.h"
#include "skeleton_attack_state.h"

namespace albinjohansson::wanderer {

SkeletonStateMachine::SkeletonStateMachine(IEntity* entity)
    : AbstractEntityStateMachine(entity) {

  // TODO add different states
  put(EntityStateID::Idle, std::make_unique<SkeletonIdleState>(this));
  put(EntityStateID::Walk, std::make_unique<SkeletonMovingState>(this));
  put(EntityStateID::Attack, std::make_unique<SkeletonAttackState>(this));
}

SkeletonStateMachine::~SkeletonStateMachine() = default;

}
