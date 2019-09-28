#include "input_handler.h"

using namespace centurion::input;
using namespace wanderer::model;

namespace wanderer::controller {

void InputHandler::CheckMovementInput(const centurion::input::KeyState& state) {
  const bool up = state.IsHeldDown(SDL_SCANCODE_W);
  const bool down = state.IsHeldDown(SDL_SCANCODE_S);

  if (up && down) {
    controller->StopPlayer(Direction::UP);
    controller->StopPlayer(Direction::DOWN);
  } else {
    if (up) {
      controller->MovePlayer(Direction::UP);
    }

    if (down) {
      controller->MovePlayer(Direction::DOWN);
    }
  }

  if (state.WasReleased(SDL_SCANCODE_W)) {
    controller->StopPlayer(Direction::UP);
  }

  if (state.WasReleased(SDL_SCANCODE_S)) {
    controller->StopPlayer(Direction::DOWN);
  }

  const bool right = state.IsHeldDown(SDL_SCANCODE_D);
  const bool left = state.IsHeldDown(SDL_SCANCODE_A);
  if (right && left) {
    controller->StopPlayer(Direction::RIGHT);
    controller->StopPlayer(Direction::LEFT);
  } else {
    if (right) {
      controller->MovePlayer(Direction::RIGHT);
    }

    if (left) {
      controller->MovePlayer(Direction::LEFT);
    }
  }

  if (state.WasReleased(SDL_SCANCODE_A)) {
    controller->StopPlayer(Direction::LEFT);
  }

  if (state.WasReleased(SDL_SCANCODE_D)) {
    controller->StopPlayer(Direction::RIGHT);
  }
}

void InputHandler::KeyStateUpdated(const KeyState& state) {
  if (state.WasReleased(SDL_SCANCODE_ESCAPE)) {
    controller->Exit();
    return;
  }

  CheckMovementInput(state);
}

void InputHandler::MouseStateUpdated(const centurion::input::MouseState& mouse) {
  // TODO delegate to mouse handler
}

} // namespace wanderer::controller