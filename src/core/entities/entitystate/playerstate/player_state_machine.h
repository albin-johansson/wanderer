#pragma once
#include "entity_state_machine.h"
#include <memory>

namespace albinjohansson::wanderer {

class Input;
class IWandererCore;

/**
 * The IPlayerStateMachine interface is a subinterface of IEntityStateMachine that specifies
 * state machines for player instances.
 *
 * @see IEntityStateMachine
 * @since 0.1.0
 */
class IPlayerStateMachine : public virtual IEntityStateMachine {
 protected:
  IPlayerStateMachine() = default;

 public:
  ~IPlayerStateMachine() override = default;

  /**
   * Reacts to the input.
   *
   * @param input a reference to the input state.
   * @since 0.1.0
   */
  virtual void HandleInput(const Input& input, const IWandererCore& core) = 0;
};

}
