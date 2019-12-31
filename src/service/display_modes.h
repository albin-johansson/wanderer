#pragma once
#include <SDL.h>

namespace albinjohansson::wanderer {

/**
 * The DisplayModes class is a service that provides information about display modes.
 *
 * @since 0.1.0
 */
class DisplayModes final {
 public:
  DisplayModes() = delete;

  ~DisplayModes() = default;

  /**
   * Returns the desktop display mode.
   *
   * @return the desktop display mode.
   * @throws BadStateException if the desktop info cannot be deduced.
   * @since 0.1.0
   */
  [[nodiscard]]
  static SDL_DisplayMode GetDesktopInfo();
};

}
