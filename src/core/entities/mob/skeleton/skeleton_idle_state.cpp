#include "skeleton_idle_state.h"
#include "player.h"
#include "skeleton.h"

namespace albinjohansson::wanderer {

SkeletonIdleState::SkeletonIdleState(IEntityStateMachine* parent)
    : idleDelegate(EntityIdleDelegate(parent)) {}

SkeletonIdleState::~SkeletonIdleState() = default;

void SkeletonIdleState::Tick(const ILevel& level, float delta) {

  auto& entity = idleDelegate.GetParent().GetEntity();
  float distance = entity.GetPosition().DistanceTo(level.GetPlayer().GetPosition());

  if (distance <= Skeleton::HOMING_RANGE || (SDL_GetTicks() - enterTime) >= 2000) {
    idleDelegate.GetParent().SetState(EntityStateID::WALK, level);
  }
}

void SkeletonIdleState::Draw(Renderer& renderer, const Viewport& viewport) const {
  idleDelegate.Draw(renderer, viewport);
}

void SkeletonIdleState::Enter(const ILevel& level) {
  idleDelegate.Enter(level);
  enterTime = SDL_GetTicks();
}

void SkeletonIdleState::Exit(const ILevel& level) {
  idleDelegate.Exit(level);
}

}
