#pragma once
#include <SDL.h>
#include <vector>
#include <cstdint>

namespace albinjohansson::wanderer {

class KeyStateManager final {
 private:
  std::vector<uint8_t> prevStates;
  const uint8_t* stateArr = nullptr;
  int nKeys = 0;

  void copy_states();

 public:
  KeyStateManager();

  ~KeyStateManager();

  /**
   * Updates the key state.
   *
   * @since 0.1.0
   */
  void update();

  /**
   * Indicates whether or not the key associated with the specified scancode is pressed.
   *
   * @param scancode the scancode of the key to check.
   * @return true if the key associated with the specified scancode is pressed; false otherwise.
   * @since 0.1.0
   */
  [[nodiscard]]
  bool is_pressed(SDL_Scancode scancode) const;

  /**
   * Indicates whether or not the key associated with the specified scancode was just pressed.
   *
   * @param scancode the scancode of the key to check.
   * @return true if the key associated with the specified scancode was just pressed; false
   * otherwise.
   * @since 0.1.0
   */
  [[nodiscard]]
  bool was_just_pressed(SDL_Scancode scancode) const;

  /**
   * Indicates whether or not the key associated with the specified scancode was released.
   *
   * @param scancode the scancode of the key to check.
   * @return true if the key associated with the specified scancode was released; false otherwise.
   * @since 0.1.0
   */
  [[nodiscard]]
  bool was_released(SDL_Scancode scancode) const;

};

}

