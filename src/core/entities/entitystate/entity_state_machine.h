#pragma once
#include <memory>
#include "drawable.h"
#include "entity_state_id.h"
#include "entity.h"
#include "input.h"

namespace albinjohansson::wanderer {

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

  virtual void Tick(const IWandererCore& core, float delta) = 0;

  /**
   * Changes the currently active entity state.
   *
   * @param id the id of the desired entity state.
   * @since 0.1.0
   */
  virtual void SetState(EntityStateID id, const IWandererCore& core) = 0;

  [[nodiscard]] virtual IEntity& GetEntity() = 0;
};

using IEntityStateMachine_uptr = std::unique_ptr<IEntityStateMachine>;
using IEntityStateMachine_sptr = std::shared_ptr<IEntityStateMachine>;
using IEntityStateMachine_wptr = std::weak_ptr<IEntityStateMachine>;

}
