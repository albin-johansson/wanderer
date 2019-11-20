#include "mouse_state_manager.h"
#include <SDL.h>

namespace wanderer::controller {

MouseStateManager::MouseStateManager() = default;

MouseStateManager::~MouseStateManager() = default;

MouseStateManager_uptr MouseStateManager::Create() {
  return std::make_unique<MouseStateManager>();
}

void MouseStateManager::Update() {
  prevLeftPressed = leftPressed;
  prevRightPressed = rightPressed;

  auto newX = 0;
  auto newY = 0;
  Uint32 mask = SDL_GetMouseState(&newX, &newY);
  mouseX = static_cast<float>(newX);
  mouseY = static_cast<float>(newY);

  leftPressed = mask & SDL_BUTTON(SDL_BUTTON_LEFT);
  rightPressed = mask & SDL_BUTTON(SDL_BUTTON_RIGHT);

  auto adjustedX = (mouseX / windowWidth) * logicalWidth;
  auto adjustedY = (mouseY / windowHeight) * logicalHeight;
  mouseX = adjustedX;
  mouseY = adjustedY;
}

void MouseStateManager::SetWindowWidth(int width) {
  windowWidth = static_cast<float>(width);
}

void MouseStateManager::SetWindowHeight(int height) {
  windowHeight = static_cast<float>(height);
}

void MouseStateManager::SetLogicalWidth(int width) {
  logicalWidth = static_cast<float>(width);
}

void MouseStateManager::SetLogicalHeight(int height) {
  logicalHeight = static_cast<float>(height);
}

}
