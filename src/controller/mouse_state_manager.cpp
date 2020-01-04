#include "mouse_state_manager.h"
#include "window.h"
#include <SDL.h>
#include <cstdint>

namespace albinjohansson::wanderer {

MouseStateManager::MouseStateManager() noexcept = default;

MouseStateManager::~MouseStateManager() = default;

void MouseStateManager::WindowUpdated(const Window& window) noexcept {
  windowWidth = static_cast<float>(window.GetWidth());
  windowHeight = static_cast<float>(window.GetHeight());
}

void MouseStateManager::Update() {
  prevLeftPressed = leftPressed;
  prevRightPressed = rightPressed;

  oldX = mouseX;
  oldY = mouseY;

  auto newX = 0;
  auto newY = 0;
  const auto mask = SDL_GetMouseState(&newX, &newY);
  mouseX = static_cast<float>(newX);
  mouseY = static_cast<float>(newY);

  leftPressed = mask & SDL_BUTTON(SDL_BUTTON_LEFT);
  rightPressed = mask & SDL_BUTTON(SDL_BUTTON_RIGHT);

  const auto adjustedX = (mouseX / windowWidth) * logicalWidth;
  const auto adjustedY = (mouseY / windowHeight) * logicalHeight;
  mouseX = adjustedX;
  mouseY = adjustedY;
}

void MouseStateManager::SetLogicalWidth(int width) {
  logicalWidth = static_cast<float>(width);
}

void MouseStateManager::SetLogicalHeight(int height) {
  logicalHeight = static_cast<float>(height);
}

float MouseStateManager::GetMouseX() const noexcept {
  return mouseX;
}

float MouseStateManager::GetMouseY() const noexcept {
  return mouseY;
}

bool MouseStateManager::IsLeftButtonPressed() const noexcept {
  return leftPressed;
}

bool MouseStateManager::IsRightButtonPressed() const noexcept {
  return rightPressed;
}

bool MouseStateManager::WasMouseMoved() const noexcept {
  return oldX != mouseX || oldY != mouseY;
}

bool MouseStateManager::WasLeftButtonReleased() const noexcept {
  return !leftPressed && prevLeftPressed;
}

bool MouseStateManager::WasRightButtonReleased() const noexcept {
  return !rightPressed && prevRightPressed;
}

}
