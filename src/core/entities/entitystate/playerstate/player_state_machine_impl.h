#pragma once
#include "abstract_entity_state_machine.h"
#include "player_state_machine.h"
#include "player_state.h"

namespace albinjohansson::wanderer {

class IEntity;

/**
 * The PlayerStateMachineImpl class is an implementation of the IPlayerStateMachine interface.
 *
 * @see IPlayerStateMachine
 * @since 0.1.0
 */
class PlayerStateMachineImpl final : public IPlayerStateMachine,
                                     public AbstractEntityStateMachine<IPlayerState> {
 public:
  /**
   * @param entity a pointer to the associated entity instance, will not be freed by the created
   * state machine.
   * @throws NullPointerException if any pointers are null.
   * @since 0.1.0
   */
  explicit PlayerStateMachineImpl(IEntity* entity);

  ~PlayerStateMachineImpl() override;

  void HandleInput(const Input& input, const IWandererCore& core) override;

};

}
