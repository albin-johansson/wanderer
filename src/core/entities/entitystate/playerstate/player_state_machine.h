#pragma once
#include "entity_state_machine.h"
#include "input.h"
#include <memory>

namespace albinjohansson::wanderer {

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
  virtual void HandleInput(const Input& input, const ILevel& level) = 0;
};

using IPlayerStateMachine_uptr = std::unique_ptr<IPlayerStateMachine>;
using IPlayerStateMachine_sptr = std::shared_ptr<IPlayerStateMachine>;
using IPlayerStateMachine_wptr = std::weak_ptr<IPlayerStateMachine>;

}
