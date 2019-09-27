#include "input_handler.h"
#include <iostream>

using namespace centurion::input;

namespace wanderer::controller {

void InputHandler::CheckMovementInput(const centurion::input::KeyState& state) {
  if (state.IsHeldDown(SDL_SCANCODE_W)) {
    std::cout << "Holding the 'W' key!\n";
  }

  if (state.IsHeldDown(SDL_SCANCODE_S)) {
    std::cout << "Holding the 'S' key!\n";
  }

  if (state.IsHeldDown(SDL_SCANCODE_D)) {
    std::cout << "Holding the 'D' key!\n";
  }

  if (state.IsHeldDown(SDL_SCANCODE_A)) {
    std::cout << "Holding the 'A' key!\n";
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