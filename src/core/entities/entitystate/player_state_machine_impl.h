#pragma once
#include "player_state_machine.h"
#include "player_state.h"
#include "game.h"
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
  IEntity* entity = nullptr;
  IGame_sptr game = nullptr;
  EntityStateID activeStateID;
  std::map<EntityStateID, IPlayerState_uptr> states;

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

  void Draw(visuals::Renderer& renderer, const Viewport& viewport) const noexcept override;

  void HandleInput(const Input& input, const IGame& game) override;

  void SetState(EntityStateID id, const IGame& game) override;

  void Tick(const IGame& game, float delta) override;
};

}
