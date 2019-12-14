#include "player_dying_state.h"
#include "entity.h"

namespace albinjohansson::wanderer {

PlayerDyingState::PlayerDyingState(IEntity* entity)
    : dyingDelegate(entity) {}

PlayerDyingState::~PlayerDyingState() = default;

void PlayerDyingState::HandleInput(const Input& input, const IWandererCore& core) {}

void PlayerDyingState::Draw(Renderer& renderer, const Viewport& viewport) const {
  dyingDelegate.Draw(renderer, viewport);
}

void PlayerDyingState::Tick(const IWandererCore& core, float delta) {
  dyingDelegate.Tick(core, delta);
}

void PlayerDyingState::Enter(const IWandererCore& core) {
  dyingDelegate.Enter(core);
}

void PlayerDyingState::Exit(const IWandererCore& core) {
  dyingDelegate.Exit(core);
}

}
