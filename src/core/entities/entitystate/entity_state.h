#pragma once
#include "drawable.h"
#include "input.h"
#include "wanderer_core.h"
#include <memory>

namespace albinjohansson::wanderer {

/**
 * The IEntityState interface specifies objects that represent the state of an entity at some
 * point in time.
 *
 * @see ITickable
 * @see IDrawable
 * @since 0.1.0
 */
class IEntityState : public IDrawable {
 protected:
  IEntityState() = default;

 public:
  ~IEntityState() override = default;

  virtual void Tick(const IWandererCore& core, float delta) = 0;

  /**
   * Enters the entity state.
   *
   * @param core a reference to the level.
   * @since 0.1.0
   */
  virtual void Enter(const IWandererCore& core) = 0;

  /**
   * Exits the entity state.
   *
   * @param core a reference to the level.
   * @since 0.1.0
   */
  virtual void Exit(const IWandererCore& core) = 0;

};

using IEntityState_uptr = std::unique_ptr<IEntityState>;
using IEntityState_sptr = std::shared_ptr<IEntityState>;
using IEntityState_wptr = std::weak_ptr<IEntityState>;

}