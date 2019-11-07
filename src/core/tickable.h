#pragma once

namespace wanderer::core {

/**
 * The ITickable interface specifies objects that can be updated using a delta time factor.
 *
 * @since 0.1.0
 */
class ITickable {
 protected:
  ITickable() = default;

 public:
  virtual ~ITickable() = default;

  /**
   * Updates the state of the object.
   *
   * @param delta the delta time that will be used, in seconds.
   * @since 0.1.0
   */
  virtual void Tick(float delta) = 0;

};

}