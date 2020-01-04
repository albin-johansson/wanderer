#include "input.h"
#include "key_state_manager.h"
#include "mouse_state_manager.h"
#include "require.h"

namespace albinjohansson::wanderer {

Input::Input(std::unique_ptr<KeyStateManager>&& ksm,
             std::unique_ptr<MouseStateManager>&& msm) {
  this->keyStateManager = Require::not_null(std::move(ksm));
  this->mouseStateManager = Require::not_null(std::move(msm));
}

Input::~Input() = default;

void Input::update() {
  mouseStateManager->update();
  keyStateManager->update();
  SDL_PumpEvents();
}

bool Input::is_pressed(SDL_Scancode scancode) const {
  return keyStateManager->is_pressed(scancode);
}

bool Input::was_just_pressed(SDL_Scancode scancode) const {
  return keyStateManager->was_just_pressed(scancode);
}

bool Input::was_released(SDL_Scancode scancode) const {
  return keyStateManager->was_released(scancode);
}

float Input::get_mouse_x() const noexcept {
  return mouseStateManager->get_mouse_x();
}

float Input::get_mouse_y() const noexcept {
  return mouseStateManager->get_mouse_y();
}

bool Input::is_left_button_pressed() const noexcept {
  return mouseStateManager->is_left_button_pressed();
}

bool Input::is_right_button_pressed() const noexcept {
  return mouseStateManager->is_right_button_pressed();
}

bool Input::was_left_button_released() const noexcept {
  return mouseStateManager->was_left_button_released();
}

bool Input::was_right_button_released() const noexcept {
  return mouseStateManager->was_right_button_released();
}

bool Input::was_mouse_moved() const noexcept {
  return mouseStateManager->was_mouse_moved();
}

bool Input::was_quit_requested() const noexcept {
  return SDL_PeepEvents(nullptr, 0, SDL_PEEKEVENT, SDL_QUIT, SDL_QUIT) > 0;
}

}
