#include "player_idle_state.h"
#include "entity_state_machine.h"

namespace wanderer::core {

PlayerIdleState::PlayerIdleState(IEntity* entity, IEntityStateMachine* parent)
    : idleDelegate(EntityIdleDelegate(entity, parent)) {}

PlayerIdleState::~PlayerIdleState() = default;

void PlayerIdleState::HandleInput(const Input& input) {
  if (input.IsPressed(SDL_SCANCODE_D)
      || input.IsPressed(SDL_SCANCODE_A)
      || input.IsPressed(SDL_SCANCODE_W)
      || input.IsPressed(SDL_SCANCODE_S)) {
    idleDelegate.GetParent()->SetState(EntityStateID::WALK);
  } else if (input.IsPressed(SDL_SCANCODE_SPACE)) {
    idleDelegate.GetParent()->SetState(EntityStateID::ATTACK);
  } else if (input.IsPressed(SDL_SCANCODE_U)) {
    idleDelegate.GetParent()->SetState(EntityStateID::DIE);
  }

  // TODO attack...
}

}
