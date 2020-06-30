#pragma once

#include "key.h"
#include "key_state.h"
#include "mouse_state.h"
#include "wanderer_stdinc.h"

namespace wanderer {

class Input final {
 public:
  Input() noexcept;

  void update(int windowWidth, int windowHeight) noexcept;

  [[nodiscard]] auto is_pressed(const ctn::Key& key) const noexcept -> bool;

  [[nodiscard]] auto was_just_pressed(const ctn::Key& key) const noexcept
      -> bool;

  [[nodiscard]] auto was_released(const ctn::Key& key) const noexcept -> bool;

  [[nodiscard]] auto get_mouse_x() const noexcept -> float;

  [[nodiscard]] auto get_mouse_y() const noexcept -> float;

  [[nodiscard]] auto is_left_button_pressed() const noexcept -> bool;

  [[nodiscard]] auto is_right_button_pressed() const noexcept -> bool;

  [[nodiscard]] auto was_left_button_released() const noexcept -> bool;

  [[nodiscard]] auto was_right_button_released() const noexcept -> bool;

  [[nodiscard]] auto was_mouse_moved() const noexcept -> bool;

  [[nodiscard]] auto was_quit_requested() const noexcept -> bool;

 private:
  ctn::input::KeyState m_keyState;
  ctn::input::MouseState m_mouseState;
};

}  // namespace wanderer