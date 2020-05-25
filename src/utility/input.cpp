#include "input.h"

using namespace centurion;

namespace wanderer {

void Input::update(int windowWidth, int windowHeight) noexcept
{
  m_mouseState.update(windowWidth, windowHeight);
  m_keyState.update();
  SDL_PumpEvents();
}

bool Input::is_pressed(const Key& key) const noexcept
{
  return m_keyState.is_pressed(key);
}

bool Input::was_just_pressed(const Key& key) const noexcept
{
  return m_keyState.was_just_pressed(key);
}

bool Input::was_released(const Key& key) const noexcept
{
  return m_keyState.was_just_released(key);
}

float Input::get_mouse_x() const noexcept
{
  return static_cast<float>(m_mouseState.mouse_x());
}

float Input::get_mouse_y() const noexcept
{
  return static_cast<float>(m_mouseState.mouse_y());
}

bool Input::is_left_button_pressed() const noexcept
{
  return m_mouseState.is_left_button_pressed();
}

bool Input::is_right_button_pressed() const noexcept
{
  return m_mouseState.is_right_button_pressed();
}

bool Input::was_left_button_released() const noexcept
{
  return m_mouseState.was_left_button_released();
}

bool Input::was_right_button_released() const noexcept
{
  return m_mouseState.was_right_button_released();
}

bool Input::was_mouse_moved() const noexcept
{
  return m_mouseState.was_mouse_moved();
}

bool Input::was_quit_requested() const noexcept
{
  return SDL_PeepEvents(nullptr, 0, SDL_PEEKEVENT, SDL_QUIT, SDL_QUIT) > 0;
}

}  // namespace wanderer
