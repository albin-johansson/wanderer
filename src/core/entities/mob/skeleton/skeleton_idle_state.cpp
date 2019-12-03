#include "skeleton_idle_state.h"
#include "player.h"
#include "skeleton.h"

namespace albinjohansson::wanderer {

SkeletonIdleState::SkeletonIdleState(IEntityStateMachine* parent)
    : idleDelegate(EntityIdleDelegate(parent)) {}

SkeletonIdleState::~SkeletonIdleState() = default;

void SkeletonIdleState::Tick(const IWandererCore& core, float delta) {

  auto& entity = idleDelegate.GetParent().GetEntity();
  float distance = entity.GetPosition().DistanceTo(core.GetPlayer().GetPosition());

  if (distance <= Skeleton::HOMING_RANGE || (SDL_GetTicks() - enterTime) >= 2000) {
    idleDelegate.GetParent().SetState(EntityStateID::WALK, core);
  }
}

void SkeletonIdleState::Draw(Renderer& renderer, const Viewport& viewport) const {
  idleDelegate.Draw(renderer, viewport);
}

void SkeletonIdleState::Enter(const IWandererCore& core) {
  idleDelegate.Enter(core);
  enterTime = SDL_GetTicks();
}

void SkeletonIdleState::Exit(const IWandererCore& core) {
  idleDelegate.Exit(core);
}

}
