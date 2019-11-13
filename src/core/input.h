#pragma once
#include <SDL_scancode.h>
#include "key_state_manager.h"

namespace wanderer::core {

class Input final {
 private:
  controller::KeyStateManager_sptr keyStateManager = nullptr;

 public:
  explicit Input(controller::KeyStateManager_sptr keyStateManager); // FIXME dependency

  ~Input();

  /**
   * Indicates whether or not the key associated with the specified scancode is pressed.
   *
   * @param scancode the scancode of the key to check.
   * @return true if the key associated with the specified scancode is pressed; false otherwise.
   * @since 0.1.0
   */
  [[nodiscard]] bool IsPressed(SDL_Scancode scancode) const;

  /**
   * Indicates whether or not the key associated with the specified scancode was just pressed.
   *
   * @param scancode the scancode of the key to check.
   * @return true if the key associated with the specified scancode was just pressed; false
   * otherwise.
   * @since 0.1.0
   */
  [[nodiscard]] bool WasJustPressed(SDL_Scancode scancode) const;

  /**
   * Indicates whether or not the key associated with the specified scancode was released.
   *
   * @param scancode the scancode of the key to check.
   * @return true if the key associated with the specified scancode was released; false otherwise.
   * @since 0.1.0
   */
  [[nodiscard]] bool WasReleased(SDL_Scancode scancode) const;

};

}
