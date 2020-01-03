#include "player_attack_state.h"

namespace albinjohansson::wanderer {

PlayerAttackState::PlayerAttackState(IEntityStateMachine* parent)
    : attackDelegate(parent) {}

PlayerAttackState::~PlayerAttackState() = default;

void PlayerAttackState::HandleInput(const Input&, const IWandererCore&) {
}

void PlayerAttackState::Draw(const Renderer& renderer, const Viewport& viewport) const {
  attackDelegate.Draw(renderer, viewport);
}

void PlayerAttackState::Tick(const IWandererCore& core, float delta) {
  attackDelegate.Tick(core, delta);
}

void PlayerAttackState::Enter(const IWandererCore& core) {
  attackDelegate.Enter(core);
}

void PlayerAttackState::Exit(const IWandererCore& core) {
  attackDelegate.Exit(core);
}

}
