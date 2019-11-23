#pragma once
#include <SDL.h>
#include <vector>
#include <memory>

namespace albinjohansson::wanderer {

class KeyStateManager;

using KeyStateManager_uptr = std::unique_ptr<KeyStateManager>;
using KeyStateManager_sptr = std::shared_ptr<KeyStateManager>;
using KeyStateManager_wptr = std::weak_ptr<KeyStateManager>;

class KeyStateManager final {
 private:
  std::vector<Uint8> prevStates;
  const Uint8* stateArr;
  int nKeys;

  void CopyStates();

 public:
  KeyStateManager();

  ~KeyStateManager();

  static KeyStateManager_uptr Create();

  /**
   * Updates the key state.
   *
   * @since 0.1.0
   */
  void Update();

  /**
   * Indicates whether or not the key associated with the specified scancode is pressed.
   *
   * @param scancode the scancode of the key to check.
   * @return true if the key associated with the specified scancode is pressed; false otherwise.
   * @since 0.1.0
   */
  bool IsPressed(SDL_Scancode scancode) const;

  /**
   * Indicates whether or not the key associated with the specified scancode was just pressed.
   *
   * @param scancode the scancode of the key to check.
   * @return true if the key associated with the specified scancode was just pressed; false
   * otherwise.
   * @since 0.1.0
   */
  bool WasJustPressed(SDL_Scancode scancode) const;

  /**
   * Indicates whether or not the key associated with the specified scancode was released.
   *
   * @param scancode the scancode of the key to check.
   * @return true if the key associated with the specified scancode was released; false otherwise.
   * @since 0.1.0
   */
  bool WasReleased(SDL_Scancode scancode) const;

};

}

