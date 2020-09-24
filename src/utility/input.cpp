#include "input.hpp"

#include "game_constants.hpp"

namespace wanderer {

input::input() noexcept
{
  m_mouseState.set_logical_width(g_logicalWidth<>);
  m_mouseState.set_logical_height(g_logicalHeight<>);
}

void input::update(const int windowWidth, const int windowHeight) noexcept
{
  m_mouseState.update(windowWidth, windowHeight);
  m_keyState.update();
  SDL_PumpEvents();
}

bool input::is_pressed(const cen::key_code& key) const noexcept
{
  return m_keyState.is_pressed(key);
}

bool input::was_just_pressed(const cen::key_code& key) const noexcept
{
  return m_keyState.was_just_pressed(key);
}

bool input::was_released(const cen::key_code& key) const noexcept
{
  return m_keyState.was_just_released(key);
}

float input::mouse_x() const noexcept
{
  return static_cast<float>(m_mouseState.mouse_x());
}

float input::mouse_y() const noexcept
{
  return static_cast<float>(m_mouseState.mouse_y());
}

bool input::is_left_button_pressed() const noexcept
{
  return m_mouseState.is_left_button_pressed();
}

bool input::is_right_button_pressed() const noexcept
{
  return m_mouseState.is_right_button_pressed();
}

bool input::was_left_button_released() const noexcept
{
  return m_mouseState.was_left_button_released();
}

bool input::was_right_button_released() const noexcept
{
  return m_mouseState.was_right_button_released();
}

bool input::was_mouse_moved() const noexcept
{
  return m_mouseState.was_mouse_moved();
}

bool input::was_quit_requested() const noexcept
{
  return SDL_PeepEvents(nullptr, 0, SDL_PEEKEVENT, SDL_QUIT, SDL_QUIT) > 0;
}

}  // namespace wanderer