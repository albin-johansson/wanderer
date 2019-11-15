#include "mouse_state_manager.h"
#include <SDL.h>

namespace wanderer::controller {

MouseStateManager::MouseStateManager() {
  prevLeftPressed = false;
  prevRightPressed = false;
  leftPressed = false;
  rightPressed = false;
}

MouseStateManager::~MouseStateManager() = default;

MouseStateManager_uptr MouseStateManager::CreateUnique() {
  return std::make_unique<MouseStateManager>();
}

void MouseStateManager::Update() {
  prevLeftPressed = leftPressed;
  prevRightPressed = rightPressed;

  Uint32 mask = SDL_GetMouseState(&mouseX, &mouseY);

  leftPressed = mask & SDL_BUTTON(SDL_BUTTON_LEFT);
  rightPressed = mask & SDL_BUTTON(SDL_BUTTON_RIGHT);

  // TODO switch to floats instead of ints to avoid casting every update
  auto adjustedX = (float(mouseX) / float(windowWidth)) * float(logicalWidth);
  auto adjustedY = (float(mouseY) / float(windowHeight)) * float(logicalHeight);
  mouseX = adjustedX;
  mouseY = adjustedY;
}

void MouseStateManager::SetWindowWidth(int width) {
  windowWidth = width;
}

void MouseStateManager::SetWindowHeight(int height) {
  windowHeight = height;
}

void MouseStateManager::SetLogicalWidth(int width) {
  logicalWidth = width;
}

void MouseStateManager::SetLogicalHeight(int height) {
  logicalHeight = height;
}

}
