#include "input.h"
#include "require.h"

using namespace centurion;

namespace albinjohansson::wanderer {

Input::Input(std::unique_ptr<KeyState>&& ksm,
             std::unique_ptr<MouseState>&& msm) {
  this->keyState = Require::not_null(std::move(ksm));
  this->mouseState = Require::not_null(std::move(msm));
}

Input::~Input() = default;

void Input::update() {
  mouseState->update();
  keyState->update();
  SDL_PumpEvents();
}

bool Input::is_pressed(SDL_Scancode scancode) const {
  return keyState->is_pressed(scancode);
}

bool Input::was_just_pressed(SDL_Scancode scancode) const {
  return keyState->was_just_pressed(scancode);
}

bool Input::was_released(SDL_Scancode scancode) const {
  return keyState->was_just_released(scancode);
}

float Input::get_mouse_x() const noexcept {
  return mouseState->get_mouse_x();
}

float Input::get_mouse_y() const noexcept {
  return mouseState->get_mouse_y();
}

bool Input::is_left_button_pressed() const noexcept {
  return mouseState->is_left_button_pressed();
}

bool Input::is_right_button_pressed() const noexcept {
  return mouseState->is_right_button_pressed();
}

bool Input::was_left_button_released() const noexcept {
  return mouseState->was_left_button_released();
}

bool Input::was_right_button_released() const noexcept {
  return mouseState->was_right_button_released();
}

bool Input::was_mouse_moved() const noexcept {
  return mouseState->was_mouse_moved();
}

bool Input::was_quit_requested() const noexcept {
  return SDL_PeepEvents(nullptr, 0, SDL_PEEKEVENT, SDL_QUIT, SDL_QUIT) > 0;
}

}
