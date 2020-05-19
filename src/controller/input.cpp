#include "input.h"

#include "require.h"

using namespace centurion;
using namespace centurion::input;

namespace albinjohansson::wanderer {

Input::Input(UniquePtr<KeyState>&& keyState,
             const SharedPtr<centurion::input::MouseState>& mouseState)
{
  this->keyState = Require::not_null(std::move(keyState));
  this->mouseState = Require::not_null(mouseState);
}

Input::~Input() = default;

void Input::update(int windowWidth, int windowHeight) noexcept
{
  mouseState->update(windowWidth, windowHeight);
  keyState->update();
  SDL_PumpEvents();
}

bool Input::is_pressed(SDL_Scancode scancode) const noexcept
{
  return keyState->is_pressed(scancode);
}

bool Input::was_just_pressed(SDL_Scancode scancode) const noexcept
{
  return keyState->was_just_pressed(scancode);
}

bool Input::was_released(SDL_Scancode scancode) const noexcept
{
  return keyState->was_just_released(scancode);
}

float Input::get_mouse_x() const noexcept
{
  return static_cast<float>(mouseState->mouse_x());
}

float Input::get_mouse_y() const noexcept
{
  return static_cast<float>(mouseState->mouse_y());
}

bool Input::is_left_button_pressed() const noexcept
{
  return mouseState->is_left_button_pressed();
}

bool Input::is_right_button_pressed() const noexcept
{
  return mouseState->is_right_button_pressed();
}

bool Input::was_left_button_released() const noexcept
{
  return mouseState->was_left_button_released();
}

bool Input::was_right_button_released() const noexcept
{
  return mouseState->was_right_button_released();
}

bool Input::was_mouse_moved() const noexcept
{
  return mouseState->was_mouse_moved();
}

bool Input::was_quit_requested() const noexcept
{
  return SDL_PeepEvents(nullptr, 0, SDL_PEEKEVENT, SDL_QUIT, SDL_QUIT) > 0;
}

}  // namespace albinjohansson::wanderer
