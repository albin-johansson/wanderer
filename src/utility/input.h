#pragma once
#include <SDL_scancode.h>

#include <memory>

#include "key.h"
#include "key_state.h"
#include "mouse_state.h"

namespace wanderer {

class Input final {
 public:
  Input() noexcept;

  void update(int windowWidth, int windowHeight) noexcept;

  [[nodiscard]] bool is_pressed(const centurion::Key& key) const noexcept;

  [[nodiscard]] bool was_just_pressed(const centurion::Key& key) const noexcept;

  [[nodiscard]] bool was_released(const centurion::Key& key) const noexcept;

  [[nodiscard]] float get_mouse_x() const noexcept;

  [[nodiscard]] float get_mouse_y() const noexcept;

  [[nodiscard]] bool is_left_button_pressed() const noexcept;

  [[nodiscard]] bool is_right_button_pressed() const noexcept;

  [[nodiscard]] bool was_left_button_released() const noexcept;

  [[nodiscard]] bool was_right_button_released() const noexcept;

  [[nodiscard]] bool was_mouse_moved() const noexcept;

  [[nodiscard]] bool was_quit_requested() const noexcept;

 private:
  centurion::input::KeyState m_keyState;
  centurion::input::MouseState m_mouseState;
};

}  // namespace wanderer