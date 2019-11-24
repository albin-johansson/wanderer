#include "player_moving_state.h"
#include "entity_sheet.h"
#include "objects.h"
;

namespace albinjohansson::wanderer {

PlayerMovingState::PlayerMovingState(IEntityStateMachine* parent)
    : moveDelegate(parent) {
  this->parent = Objects::RequireNonNull(parent);
}

PlayerMovingState::~PlayerMovingState() = default;

void PlayerMovingState::CheckPressed(const Input& input) {
  bool left = input.IsPressed(SDL_SCANCODE_A);
  bool right = input.IsPressed(SDL_SCANCODE_D);
  bool up = input.IsPressed(SDL_SCANCODE_W);
  bool down = input.IsPressed(SDL_SCANCODE_S);
  IEntity& entity = moveDelegate.GetEntity();

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

void PlayerMovingState::CheckReleased(const Input& input) {
  bool left = input.WasReleased(SDL_SCANCODE_A);
  bool right = input.WasReleased(SDL_SCANCODE_D);
  bool up = input.WasReleased(SDL_SCANCODE_W);
  bool down = input.WasReleased(SDL_SCANCODE_S);
  auto& entity = moveDelegate.GetEntity();

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

void PlayerMovingState::HandleInput(const Input& input, const ILevel& level) {
  areMoveKeysDown = false; // assume no movement keys are down

  CheckPressed(input);
  CheckReleased(input);

  if (!areMoveKeysDown && moveDelegate.GetEntity().GetVelocity().IsZero()) {
    parent->SetState(EntityStateID::IDLE, level);
  } else if (input.IsPressed(SDL_SCANCODE_SPACE)) {
    parent->SetState(EntityStateID::ATTACK, level);
  }
}

}