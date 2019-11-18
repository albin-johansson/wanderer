#pragma once
#include "tickable.h"
#include "drawable.h"
#include "input.h"
#include <memory>

namespace wanderer::core {

/**
 * The IEntityState interface specifies objects that represent the state of an entity at some
 * point in time.
 *
 * @see ITickable
 * @see IDrawable
 * @since 0.1.0
 */
class IEntityState : public ITickable, public IDrawable {
 protected:
  IEntityState() = default;

 public:
  ~IEntityState() override = default;

  /**
   * Enters the entity state.
   *
   * @since 0.1.0
   */
  virtual void Enter() = 0;

  /**
   * Exits the entity state.
   *
   * @since 0.1.0
   */
  virtual void Exit() = 0;

};

using IEntityState_uptr = std::unique_ptr<IEntityState>;
using IEntityState_sptr = std::shared_ptr<IEntityState>;
using IEntityState_wptr = std::weak_ptr<IEntityState>;

}