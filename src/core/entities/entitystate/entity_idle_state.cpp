#include "entity_idle_state.h"
#include "entity_state_machine.h"
#include "objects.h"

namespace wanderer::core {

EntityIdleState::EntityIdleState(IEntityStateMachine* parent) {
  this->parent = Objects::RequireNonNull(parent);
}

EntityIdleState::~EntityIdleState() = default;

void EntityIdleState::Update(IEntity& entity, float delta) {
}

void EntityIdleState::HandleInput(IEntity& entity, const Input& input) {
  if (input.IsPressed(SDL_SCANCODE_D)
      || input.IsPressed(SDL_SCANCODE_A)
      || input.IsPressed(SDL_SCANCODE_W)
      || input.IsPressed(SDL_SCANCODE_S)) {
    parent->Change(EntityStateID::WALK);
    return;
  }

  // TODO attack...
}

void EntityIdleState::EnterState(IEntity& entity) {
}

void EntityIdleState::ExitState(IEntity& entity) {
}

}
