#include "mouse_state_manager.h"
#include "window.h"
#include <SDL.h>
#include <cstdint>

using namespace centurion;

namespace albinjohansson::wanderer {

MouseStateManager::MouseStateManager() noexcept = default;

MouseStateManager::~MouseStateManager() = default;

void MouseStateManager::window_updated(const Window& window) noexcept {
  windowWidth = static_cast<float>(window.get_width());
  windowHeight = static_cast<float>(window.get_height());
}

void MouseStateManager::update() {
  prevLeftPressed = leftPressed;
  prevRightPressed = rightPressed;

  oldX = mouseX;
  oldY = mouseY;

  auto newX = 0;
  auto newY = 0;
  const uint32_t mask = SDL_GetMouseState(&newX, &newY);
  mouseX = static_cast<float>(newX);
  mouseY = static_cast<float>(newY);

  leftPressed = mask & SDL_BUTTON(SDL_BUTTON_LEFT);
  rightPressed = mask & SDL_BUTTON(SDL_BUTTON_RIGHT);

  const auto adjustedX = (mouseX / windowWidth) * logicalWidth;
  const auto adjustedY = (mouseY / windowHeight) * logicalHeight;
  mouseX = adjustedX;
  mouseY = adjustedY;
}

void MouseStateManager::set_logical_width(int width) {
  logicalWidth = static_cast<float>(width);
}

void MouseStateManager::set_logical_height(int height) {
  logicalHeight = static_cast<float>(height);
}

float MouseStateManager::get_mouse_x() const noexcept {
  return mouseX;
}

float MouseStateManager::get_mouse_y() const noexcept {
  return mouseY;
}

bool MouseStateManager::is_left_button_pressed() const noexcept {
  return leftPressed;
}

bool MouseStateManager::is_right_button_pressed() const noexcept {
  return rightPressed;
}

bool MouseStateManager::was_mouse_moved() const noexcept {
  return oldX != mouseX || oldY != mouseY;
}

bool MouseStateManager::was_left_button_released() const noexcept {
  return !leftPressed && prevLeftPressed;
}

bool MouseStateManager::was_right_button_released() const noexcept {
  return !rightPressed && prevRightPressed;
}

}
