#pragma once
#include "drawable.h"
#include "entity_state_id.h"

namespace albinjohansson::wanderer {

class IWandererCore;
class IEntity;

/**
 * The IEntityStateMachine interface specifies objects that represent state machines related to
 * the states of entities.
 *
 * @since 0.1.0
 */
class IEntityStateMachine : public IDrawable {
 protected:
  IEntityStateMachine() = default;

 public:
  ~IEntityStateMachine() override = default;

  /**
   * Updates the state of the state machine.
   *
   * @param core the associated core instance.
   * @param delta the delta time, in seconds.
   * @since 0.1.0
   */
  virtual void Tick(const IWandererCore& core, float delta) = 0;

  /**
   * Changes the currently active entity state.
   *
   * @param id the id of the desired entity state.
   * @param core the associated core instance.
   * @since 0.1.0
   */
  virtual void SetState(EntityStateID id, const IWandererCore& core) = 0;

  /**
   * Returns the associated entity instance.
   *
   * @return the associated entity instance.
   * @since 0.1.0
   */
  [[nodiscard]]
  virtual IEntity& GetEntity() = 0;
};

}
