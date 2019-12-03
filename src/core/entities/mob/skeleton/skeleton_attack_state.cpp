#include "skeleton_attack_state.h"

namespace albinjohansson::wanderer {

SkeletonAttackState::SkeletonAttackState(IEntityStateMachine* parent)
    : attackDelegate(EntityAttackDelegate(parent)) {}

SkeletonAttackState::~SkeletonAttackState() = default;

void SkeletonAttackState::Draw(Renderer& renderer, const Viewport& viewport) const {
  attackDelegate.Draw(renderer, viewport);
}

void SkeletonAttackState::Enter(const IWandererCore& core) {
  attackDelegate.Enter(core);
}

void SkeletonAttackState::Exit(const IWandererCore& core) {
  attackDelegate.Exit(core);
}

void SkeletonAttackState::Tick(const IWandererCore& core, float delta) {
  attackDelegate.Tick(core, delta);
}

}
