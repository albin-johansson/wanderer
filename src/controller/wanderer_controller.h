#pragma once

namespace albinjohansson::wanderer {

/**
 * The IWandererController interface specifies the facade for the main
 * controller of the Wanderer application.
 *
 * @since 0.1.0
 */
class IWandererController {
 public:
  virtual ~IWandererController() = default;

  /**
   * Runs the application.
   *
   * @since 0.1.0
   */
  virtual void run() = 0;
};

}  // namespace albinjohansson::wanderer