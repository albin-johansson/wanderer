#pragma once
#include "drawable.h"

namespace albinjohansson::wanderer {

class IWandererCore;

/**
 * The IEntityState interface specifies objects that represent the state of an entity at some
 * point in time.
 *
 * @see IDrawable
 * @since 0.1.0
 */
class IEntityState : public IDrawable {
 public:
  ~IEntityState() override = default;

  /**
   * Updates the state.
   *
   * @param core the associated core instance.
   * @param delta the delta time, in seconds.
   * @since 0.1.0
   */
  virtual void tick(const IWandererCore& core, float delta) = 0;

  /**
   * Enters the entity state.
   *
   * @param core the associated core instance.
   * @since 0.1.0
   */
  virtual void enter(const IWandererCore& core) = 0;

  /**
   * Exits the entity state.
   *
   * @param core the associated core instance.
   * @since 0.1.0
   */
  virtual void exit(const IWandererCore& core) = 0;

};

}