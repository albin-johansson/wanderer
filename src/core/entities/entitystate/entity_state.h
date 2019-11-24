#pragma once
#include "drawable.h"
#include "level.h"
#include "input.h"
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

  virtual void Tick(const ILevel& level, float delta) = 0;

  /**
   * Enters the entity state.
   *
   * @param level a reference to the level.
   * @since 0.1.0
   */
  virtual void Enter(const ILevel& level) = 0;

  /**
   * Exits the entity state.
   *
   * @param level a reference to the level.
   * @since 0.1.0
   */
  virtual void Exit(const ILevel& level) = 0;

};

using IEntityState_uptr = std::unique_ptr<IEntityState>;
using IEntityState_sptr = std::shared_ptr<IEntityState>;
using IEntityState_wptr = std::weak_ptr<IEntityState>;

}