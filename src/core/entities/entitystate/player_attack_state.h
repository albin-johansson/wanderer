#pragma once
#include "player_state.h"
#include "entity.h"
#include "entity_state_machine.h"
#include "entity_attack_delegate.h"

namespace wanderer::core {

/**
 * The PlayerAttackState class is an implementation of the IPlayerState interface that represents
 * the state of the player when attacking.
 *
 * @see IPlayerState
 * @since 0.1.0
 */
class PlayerAttackState final : public IPlayerState {
 private:
  EntityAttackDelegate attackDelegate;

 public:
  /**
   * @param entity a pointer to the associated entity.
   * @param parent a pointer to the parent state machine.
   * @throws NullPointerException if any pointers are null.
   * @since 0.1.0
   */
  PlayerAttackState(IEntity* entity, IEntityStateMachine* parent);

  ~PlayerAttackState() override;

  void HandleInput(const Input& input, const IGame& game) override;

  inline void Draw(visuals::Renderer& renderer, const Viewport& viewport) const override {
    attackDelegate.Draw(renderer, viewport);
  }

  inline void Tick(const IGame& game, float delta) override { attackDelegate.Tick(game, delta); }

  inline void Enter(const IGame& game) override { attackDelegate.Enter(game); }

  inline void Exit(const IGame& game) override { attackDelegate.Exit(game); }

};

}
