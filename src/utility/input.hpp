#pragma once

#include <key_code.hpp>
#include <key_state.hpp>
#include <mouse_state.hpp>

namespace wanderer {

class Input final
{
 public:
  Input() noexcept;

  void update(int windowWidth, int windowHeight) noexcept;

  [[nodiscard]] auto is_pressed(const cen::key_code& key) const noexcept
      -> bool;

  [[nodiscard]] auto was_just_pressed(const cen::key_code& key) const noexcept
      -> bool;

  [[nodiscard]] auto was_released(const cen::key_code& key) const noexcept
      -> bool;

  [[nodiscard]] auto get_mouse_x() const noexcept -> float;

  [[nodiscard]] auto get_mouse_y() const noexcept -> float;

  [[nodiscard]] auto is_left_button_pressed() const noexcept -> bool;

  [[nodiscard]] auto is_right_button_pressed() const noexcept -> bool;

  [[nodiscard]] auto was_left_button_released() const noexcept -> bool;

  [[nodiscard]] auto was_right_button_released() const noexcept -> bool;

  [[nodiscard]] auto was_mouse_moved() const noexcept -> bool;

  [[nodiscard]] auto was_quit_requested() const noexcept -> bool;

 private:
  cen::key_state m_keyState;
  cen::mouse_state m_mouseState;
};

}  // namespace wanderer