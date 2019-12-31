#pragma once
#include "mouse_state_manager.h"
#include "key_state_manager.h"
#include <SDL_scancode.h>
#include <memory>

namespace albinjohansson::wanderer {

class Input final {
 private:
  std::unique_ptr<KeyStateManager> keyStateManager = nullptr;
  std::unique_ptr<MouseStateManager> mouseStateManager = nullptr;

 public:
  Input(std::unique_ptr<KeyStateManager>&& keyStateManager,
        std::unique_ptr<MouseStateManager>&& mouseStateManager);

  ~Input();

  void Update();

  /**
   * Indicates whether or not the key associated with the specified scancode is pressed.
   *
   * @param scancode the scancode of the key to check.
   * @return true if the key associated with the specified scancode is pressed; false otherwise.
   * @since 0.1.0
   */
  [[nodiscard]]
  bool IsPressed(SDL_Scancode scancode) const;

  /**
   * Indicates whether or not the key associated with the specified scancode was just pressed.
   *
   * @param scancode the scancode of the key to check.
   * @return true if the key associated with the specified scancode was just pressed; false
   * otherwise.
   * @since 0.1.0
   */
  [[nodiscard]]
  bool WasJustPressed(SDL_Scancode scancode) const;

  /**
   * Indicates whether or not the key associated with the specified scancode was released.
   *
   * @param scancode the scancode of the key to check.
   * @return true if the key associated with the specified scancode was released; false otherwise.
   * @since 0.1.0
   */
  [[nodiscard]]
  bool WasReleased(SDL_Scancode scancode) const;

  [[nodiscard]]
  float GetMouseX() const noexcept;

  [[nodiscard]]
  float GetMouseY() const noexcept;

  [[nodiscard]]
  bool IsLeftButtonPressed() const noexcept;

  [[nodiscard]]
  bool IsRightButtonPressed() const noexcept;

  [[nodiscard]]
  bool WasLeftButtonReleased() const noexcept;

  [[nodiscard]]
  bool WasRightButtonReleased() const noexcept;

  [[nodiscard]]
  bool WasMouseMoved() const noexcept;

  [[nodiscard]]
  bool WasQuitRequested() const noexcept;

};

}
