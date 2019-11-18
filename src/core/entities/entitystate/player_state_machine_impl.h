#pragma once
#include "player_state_machine.h"
#include "player_state.h"
#include <memory>
#include <map>
#include "entity.h"

namespace wanderer::core {

/**
 * The PlayerStateMachineImpl class is an implementation of the IPlayerStateMachine interface.
 *
 * @see IPlayerStateMachine
 * @since 0.1.0
 */
class PlayerStateMachineImpl final : public IPlayerStateMachine {
 private:
  std::map<EntityStateID, IPlayerState_uptr> states;
  EntityStateID activeStateID;
  IEntity* entity = nullptr;

  /**
   * Registers an entity state ID key with a pointer to a player state value.
   *
   * @param id the entity state ID that will serve as the key for the player state value.
   * @param state a unique pointer to the player state instance value.
   * @since 0.1.0
   */
  void Put(EntityStateID id, IPlayerState_uptr state);

 public:
  /**
   * @param entity a pointer to the associated entity instance, will not be freed by the created
   * state machine.
   * @throws NullPointerException if the supplied pointer is null.
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
   * @throws NullPointerException if the supplied pointer is null.
   * @since 0.1.0
   */
  static IPlayerStateMachine_uptr Create(IEntity* entity);

  void Draw(visuals::Renderer& renderer, const Viewport& viewport) noexcept override;

  void HandleInput(const Input& input) override;

  void SetState(EntityStateID id) override;

  void Tick(float delta) override;
};

}
