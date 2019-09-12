#include "input_handler.h"
#include <iostream>

using namespace centurion::input;

namespace wanderer::controller {

void InputHandler::KeyStateUpdated(const KeyState& state) {
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

} // namespace wanderer::controller