#pragma once
#include "player_state.h"
#include "entity.h"
#include "entity_state_machine.h"
#include "entity_dying_delegate.h"

namespace wanderer::core {

/**
 * The PlayerDyingState class is an implementation of the IPlayerState interface that represents
 * the state of the player when dying.
 *
 * @see IPlayerState
 * @since 0.1.0
 */
class PlayerDyingState final : public IPlayerState {
 private:
  EntityDyingDelegate dyingDelegate;

 public:
  /**
   * @param entity a pointer to the associated entity.
   * @param parent a pointer to the parent state machine.
   * @throws NullPointerException if any pointers are null.
   * @since 0.1.0
   */
  PlayerDyingState(IEntity* entity, IEntityStateMachine* parent);

  ~PlayerDyingState() override;

  void HandleInput(const Input& input, const IGame& game) override;

  inline void Draw(visuals::Renderer& renderer, const Viewport& viewport) const override {
    dyingDelegate.Draw(renderer, viewport);
  }

  inline void Tick(const IGame& game, float delta) override { dyingDelegate.Tick(game, delta); }

  inline void Enter(const IGame& game) override { dyingDelegate.Enter(game); }

  // TODO game over stuff
  inline void Exit(const IGame& game) override { dyingDelegate.Exit(game); }
};

}
