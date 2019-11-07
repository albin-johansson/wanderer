#pragma once
#include <memory>

namespace wanderer::core {

/**
 * The IWandererCore interface specifies the facade of the core component of the Wanderer
 * application.
 *
 * @since 0.1.0
 */
class IWandererCore {
 protected:
  IWandererCore() = default;

 public:
  /**
   * A constant that describes the fixed time step of logic updates, in seconds.
   *
   * @since 0.1.0
   */
  static constexpr float TIME_STEP = 0.0166f;

  virtual ~IWandererCore() = default;

  /**
   * Updates the state of the core.
   *
   * @since 0.1.0
   */
  virtual void Update() = 0;

  /**
   * Renders the components in the core model.
   *
   * @since 0.1.0
   */
  virtual void Render() = 0;

};

using IWandererCore_uptr = std::unique_ptr<IWandererCore>;

}