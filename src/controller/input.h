#pragma once
#include <SDL_scancode.h>

#include <memory>

#include "key_state.h"
#include "mouse_state.h"
#include "wanderer_stdinc.h"

namespace albinjohansson::wanderer {

class Input final {
 private:
  Unique<centurion::input::KeyState> keyState = nullptr;
  Shared<centurion::input::MouseState> mouseState = nullptr;

 public:
  Input(Unique<centurion::input::KeyState>&& keyState,
        const Shared<centurion::input::MouseState>& mouseState);

  ~Input();

  void update(int windowWidth, int windowHeight);

  /**
   * Indicates whether or not the key associated with the specified scancode is
   * pressed.
   *
   * @param scancode the scancode of the key to check.
   * @return true if the key associated with the specified scancode is pressed;
   * false otherwise.
   * @since 0.1.0
   */
  [[nodiscard]] bool is_pressed(SDL_Scancode scancode) const;

  /**
   * Indicates whether or not the key associated with the specified scancode was
   * just pressed.
   *
   * @param scancode the scancode of the key to check.
   * @return true if the key associated with the specified scancode was just
   * pressed; false otherwise.
   * @since 0.1.0
   */
  [[nodiscard]] bool was_just_pressed(SDL_Scancode scancode) const;

  /**
   * Indicates whether or not the key associated with the specified scancode was
   * released.
   *
   * @param scancode the scancode of the key to check.
   * @return true if the key associated with the specified scancode was
   * released; false otherwise.
   * @since 0.1.0
   */
  [[nodiscard]] bool was_released(SDL_Scancode scancode) const;

  [[nodiscard]] float get_mouse_x() const noexcept;

  [[nodiscard]] float get_mouse_y() const noexcept;

  [[nodiscard]] bool is_left_button_pressed() const noexcept;

  [[nodiscard]] bool is_right_button_pressed() const noexcept;

  [[nodiscard]] bool was_left_button_released() const noexcept;

  [[nodiscard]] bool was_right_button_released() const noexcept;

  [[nodiscard]] bool was_mouse_moved() const noexcept;

  [[nodiscard]] bool was_quit_requested() const noexcept;
};

}  // namespace albinjohansson::wanderer
