#include "skeleton_idle_state.h"
#include "entity_state_machine.h"
#include "player.h"
#include "skeleton.h"
#include "wanderer_core.h"
#include "time_utils.h"

namespace albinjohansson::wanderer {

SkeletonIdleState::SkeletonIdleState(IEntityStateMachine* parent)
    : idleDelegate(EntityIdleDelegate(parent)) {}

SkeletonIdleState::~SkeletonIdleState() = default;

void SkeletonIdleState::Tick(const IWandererCore& core, float /*delta*/) {

  auto& entity = idleDelegate.GetParent().GetEntity();
  float distance = entity.get_position().DistanceTo(core.get_player().get_position());

  if (distance <= Skeleton::HOMING_RANGE || (TimeUtils::GetMillis() - enterTime) >= 2000) {
    idleDelegate.GetParent().SetState(EntityStateID::WALK, core);
  }
}

void SkeletonIdleState::Draw(const Renderer& renderer, const Viewport& viewport) const {
  idleDelegate.Draw(renderer, viewport);
}

void SkeletonIdleState::Enter(const IWandererCore& core) {
  idleDelegate.Enter(core);
  enterTime = TimeUtils::GetMillis();
}

void SkeletonIdleState::Exit(const IWandererCore& core) {
  idleDelegate.Exit(core);
}

}
