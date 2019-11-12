#include "input.h"

#include <utility>

namespace wanderer::core {

Input::Input(controller::KeyStateManager_sptr keyStateManager) {
  this->keyStateManager = std::move(keyStateManager);
}

Input::~Input() = default;

bool Input::IsPressed(SDL_Scancode scancode) const {
  return keyStateManager->IsPressed(scancode);
}

bool Input::WasJustPressed(SDL_Scancode scancode) const {
  return keyStateManager->WasJustPressed(scancode);
}

bool Input::WasReleased(SDL_Scancode scancode) const {
  return keyStateManager->WasReleased(scancode);
}

}
