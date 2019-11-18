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

  void HandleInput(const Input& input) override;

  inline void Draw(visuals::Renderer& renderer, const Viewport& viewport) override {
    dyingDelegate.Draw(renderer, viewport);
  }

  inline void Tick(float delta) override { dyingDelegate.Tick(delta); }

  inline void Enter() override { dyingDelegate.Enter(); }

  inline void Exit() override { dyingDelegate.Exit(); } // TODO game over stuff
};

}
