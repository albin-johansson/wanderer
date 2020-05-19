#include "skeleton_state_machine.h"

#include "skeleton_attack_state.h"
#include "skeleton_dying_state.h"
#include "skeleton_idle_state.h"
#include "skeleton_moving_state.h"

namespace albinjohansson::wanderer {

SkeletonStateMachine::SkeletonStateMachine(IEntity* entity)
    : AbstractEntityStateMachine{entity}
{
  put(EntityStateID::Idle, std::make_unique<SkeletonIdleState>(this));
  put(EntityStateID::Walk, std::make_unique<SkeletonMovingState>(this));
  put(EntityStateID::Attack, std::make_unique<SkeletonAttackState>(this));
  put(EntityStateID::Die, std::make_unique<SkeletonDyingState>(entity));
}

SkeletonStateMachine::~SkeletonStateMachine() = default;

}  // namespace albinjohansson::wanderer
