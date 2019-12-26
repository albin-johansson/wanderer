#include "skeleton_attack_state.h"
#include "entity_state_machine.h"
#include "wanderer_core.h"
#include "player.h"

namespace albinjohansson::wanderer {

SkeletonAttackState::SkeletonAttackState(IEntityStateMachine* parent)
    : attackDelegate(EntityAttackDelegate(parent)) {}

SkeletonAttackState::~SkeletonAttackState() = default;

void SkeletonAttackState::Draw(const Renderer& renderer, const Viewport& viewport) const {
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

//    entity.SetDominantDirection(Direction::RIGHT);
  // TODO update dominant direction
}

}
