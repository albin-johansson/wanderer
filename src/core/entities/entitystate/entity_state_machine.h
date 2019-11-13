#pragma once
#include <memory>
#include "tickable.h"
#include "entity_state_id.h"
#include "input.h"

namespace wanderer::core {

/**
 * The IEntityStateMachine interface specifies objects that represent state machines related to
 * the states of entities.
 *
 * @since 0.1.0
 */
class IEntityStateMachine : public ITickable {
 protected:
  IEntityStateMachine() = default;

 public:
  ~IEntityStateMachine() override = default;

  /**
   * Handles the supplied input.
   *
   * @param input a reference to the input state.
   * @since 0.1.0
   */
  virtual void HandleInput(const Input& input) = 0;

  /**
   * Changes the currently active entity state.
   *
   * @param id the id of the desired entity state.
   * @since 0.1.0
   */
  virtual void Change(EntityStateID id) = 0;

};

using IEntityStateMachine_uptr = std::unique_ptr<IEntityStateMachine>;

}
