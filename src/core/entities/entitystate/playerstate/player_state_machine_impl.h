#pragma once
#include "abstract_entity_state_machine.h"
#include "player_state_machine.h"
#include "player_state.h"
#include "entity.h"

namespace albinjohansson::wanderer {

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

  /**
   * Creates and returns a unique pointer to a player state machine instance.
   *
   * @param entity a pointer to the associated entity instance, will not be freed by the created
   * state machine.
   * @return a unique pointer to a player state machine instance.
   * @throws NullPointerException if any pointers are null.
   * @since 0.1.0
   */
  static IPlayerStateMachine_uptr Create(IEntity* entity);

  void HandleInput(const Input& input, const IWandererCore& core) override;
};

}
