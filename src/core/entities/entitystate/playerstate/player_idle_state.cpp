#include "player_idle_state.h"
#include "entity_state_machine.h"
#include "input.h"

namespace albinjohansson::wanderer {

PlayerIdleState::PlayerIdleState(IEntityStateMachine* parent)
    : idleDelegate(EntityIdleDelegate(parent)) {}

PlayerIdleState::~PlayerIdleState() = default;

void PlayerIdleState::HandleInput(const Input& input, const IWandererCore& core) {
  if (input.IsPressed(SDL_SCANCODE_D)
      || input.IsPressed(SDL_SCANCODE_A)
      || input.IsPressed(SDL_SCANCODE_W)
      || input.IsPressed(SDL_SCANCODE_S)) {
    idleDelegate.GetParent().SetState(EntityStateID::WALK, core);
  } else if (input.IsPressed(SDL_SCANCODE_SPACE)) {
    idleDelegate.GetParent().SetState(EntityStateID::ATTACK, core);
  } else if (input.IsPressed(SDL_SCANCODE_U)) {
    idleDelegate.GetParent().SetState(EntityStateID::DIE, core);
  }

  // TODO attack...
}

void PlayerIdleState::Draw(Renderer& renderer, const Viewport& viewport) const noexcept {
  idleDelegate.Draw(renderer, viewport);
}

void PlayerIdleState::Tick(const IWandererCore& core, float delta) {
  idleDelegate.Tick(core, delta);
}

void PlayerIdleState::Enter(const IWandererCore& core) {
  idleDelegate.Enter(core);
}

void PlayerIdleState::Exit(const IWandererCore& core) {
  idleDelegate.Exit(core);
}

}
