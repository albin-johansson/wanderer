#include "entity_moving_state.h"
#include "movable_delegate.h"
#include "entity_state_machine.h"
#include "objects.h"

namespace wanderer::core {

EntityMovingState::EntityMovingState(IEntityStateMachine* parent) {
  this->parent = Objects::RequireNonNull(parent);
}

EntityMovingState::~EntityMovingState() = default;

void EntityMovingState::CheckPressed(IEntity& entity, const Input& input) {
  bool left = input.IsPressed(SDL_SCANCODE_A);
  bool right = input.IsPressed(SDL_SCANCODE_D);
  bool up = input.IsPressed(SDL_SCANCODE_W);
  bool down = input.IsPressed(SDL_SCANCODE_S);

  if (left && right) {
    entity.Stop(Direction::LEFT);
    entity.Stop(Direction::RIGHT);
  } else if (left) {
    entity.Move(Direction::LEFT);
  } else if (right) {
    entity.Move(Direction::RIGHT);
  }

  if (up && down) {
    entity.Stop(Direction::UP);
    entity.Stop(Direction::DOWN);
  } else if (up) {
    entity.Move(Direction::UP);
  } else if (down) {
    entity.Move(Direction::DOWN);
  }

  areMoveKeysDown = up || down || right || left;
}

void EntityMovingState::CheckReleased(IEntity& entity, const Input& input) {
  bool left = input.WasReleased(SDL_SCANCODE_A);
  bool right = input.WasReleased(SDL_SCANCODE_D);
  bool up = input.WasReleased(SDL_SCANCODE_W);
  bool down = input.WasReleased(SDL_SCANCODE_S);

  if (left) {
    entity.Stop(Direction::LEFT);
  }

  if (right) {
    entity.Stop(Direction::RIGHT);
  }

  if (up) {
    entity.Stop(Direction::UP);
  }

  if (down) {
    entity.Stop(Direction::DOWN);
  }
}

void EntityMovingState::Update(IEntity& entity, float delta) {
  Vector2 velocity = entity.GetVelocity();
  entity.AddX(velocity.GetX() * delta);
  entity.AddY(velocity.GetY() * delta);
}

void EntityMovingState::HandleInput(IEntity& entity, const Input& input) {
  areMoveKeysDown = false; // assume no movement keys are down

  CheckPressed(entity, input);
  CheckReleased(entity, input);

  // TODO check for attack

  if (!areMoveKeysDown && entity.GetVelocity().IsZero()) {
    parent->Change(EntityStateID::IDLE);
  }
}

void EntityMovingState::EnterState(IEntity& entity) {
}

void EntityMovingState::ExitState(IEntity& entity) {
}

}