#pragma once
#include <SDL_scancode.h>
#include "key_state_manager.h"
#include "mouse_state_manager.h"

namespace albinjohansson::wanderer {

class Input final {
 private:
  KeyStateManager_sptr keyStateManager = nullptr;
  MouseStateManager_sptr mouseStateManager = nullptr;

 public:
  explicit Input(KeyStateManager_sptr keyStateManager,
                 MouseStateManager_sptr mouseStateManager); // FIXME dependency

  ~Input();

  /**
   * Indicates whether or not the key associated with the specified scancode is pressed.
   *
   * @param scancode the scancode of the key to check.
   * @return true if the key associated with the specified scancode is pressed; false otherwise.
   * @since 0.1.0
   */
  [[nodiscard]] bool IsPressed(SDL_Scancode scancode) const {
    return keyStateManager->IsPressed(scancode);
  }

  /**
   * Indicates whether or not the key associated with the specified scancode was just pressed.
   *
   * @param scancode the scancode of the key to check.
   * @return true if the key associated with the specified scancode was just pressed; false
   * otherwise.
   * @since 0.1.0
   */
  [[nodiscard]] bool WasJustPressed(SDL_Scancode scancode) const {
    return keyStateManager->WasJustPressed(scancode);
  }

  /**
   * Indicates whether or not the key associated with the specified scancode was released.
   *
   * @param scancode the scancode of the key to check.
   * @return true if the key associated with the specified scancode was released; false otherwise.
   * @since 0.1.0
   */
  [[nodiscard]] bool WasReleased(SDL_Scancode scancode) const {
    return keyStateManager->WasReleased(scancode);
  }

  [[nodiscard]] float GetMouseX() const noexcept {
    return mouseStateManager->GetMouseX();
  }

  [[nodiscard]] float GetMouseY() const noexcept {
    return mouseStateManager->GetMouseY();
  }

  [[nodiscard]] bool IsLeftButtonPressed() const noexcept {
    return mouseStateManager->IsLeftButtonPressed();
  }

  [[nodiscard]] bool IsRightButtonPressed() const noexcept {
    return mouseStateManager->IsRightButtonPressed();
  }

  [[nodiscard]] bool WasLeftButtonReleased() const noexcept {
    return mouseStateManager->WasLeftButtonReleased();
  }

  [[nodiscard]] bool WasRightButtonReleased() const noexcept {
    return mouseStateManager->WasRightButtonReleased();
  }

  [[nodiscard]] bool WasMouseMoved() const noexcept {
    return mouseStateManager->WasMouseMoved();
  }

};

}
