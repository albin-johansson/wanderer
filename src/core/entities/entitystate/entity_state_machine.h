#pragma once
#include <memory>
#include "tickable.h"
#include "drawable.h"
#include "entity_state_id.h"
#include "entity.h"
#include "input.h"
#include "game.h"

namespace wanderer::core {

/**
 * The IEntityStateMachine interface specifies objects that represent state machines related to
 * the states of entities.
 *
 * @since 0.1.0
 */
class IEntityStateMachine : public ITickable, public IDrawable {
 protected:
  IEntityStateMachine() = default;

 public:
  ~IEntityStateMachine() override = default;

  /**
   * Changes the currently active entity state.
   *
   * @param id the id of the desired entity state.
   * @since 0.1.0
   */
  virtual void SetState(EntityStateID id, const IGame& game) = 0;
};

using IEntityStateMachine_uptr = std::unique_ptr<IEntityStateMachine>;
using IEntityStateMachine_sptr = std::shared_ptr<IEntityStateMachine>;
using IEntityStateMachine_wptr = std::weak_ptr<IEntityStateMachine>;

}
