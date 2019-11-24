#include "skeleton_attack_state.h"

namespace albinjohansson::wanderer {

SkeletonAttackState::SkeletonAttackState(IEntityStateMachine* parent)
    : attackDelegate(EntityAttackDelegate(parent)) {}

SkeletonAttackState::~SkeletonAttackState() = default;

void SkeletonAttackState::Draw(Renderer& renderer, const Viewport& viewport) const {
  attackDelegate.Draw(renderer, viewport);
}

void SkeletonAttackState::Enter(const ILevel& level) {
  attackDelegate.Enter(level);
}

void SkeletonAttackState::Exit(const ILevel& level) {
  attackDelegate.Exit(level);
}

void SkeletonAttackState::Tick(const ILevel& level, float delta) {
  attackDelegate.Tick(level, delta);
}

}
