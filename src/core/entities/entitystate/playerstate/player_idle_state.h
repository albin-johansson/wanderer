#pragma once
#include "player_state.h"
#include "entity.h"
#include "entity_draw_delegate.h"
#include "entity_idle_delegate.h"

namespace albinjohansson::wanderer {

/**
 * The PlayerIdleState class is an implementation of the IPlayerState interface that represents
 * the state of the player when idle.
 *
 * @see IPlayerState
 * @since 0.1.0
 */
class PlayerIdleState final : public IPlayerState {
 private:
  EntityIdleDelegate idleDelegate;

 public:
  /**
   * @param parent a pointer to the parent entity state machine.
   * @throws NullPointerException if the supplied pointer is null.
   * @since 0.1.0
   */
  explicit PlayerIdleState(IEntityStateMachine* parent);

  ~PlayerIdleState() override;

  void HandleInput(const Input& input, const IGame& game) override;

  inline void Draw(Renderer& renderer, const Viewport& viewport) const noexcept override {
    idleDelegate.Draw(renderer, viewport);
  }

  inline void Tick(const IGame& game, float delta) override { idleDelegate.Tick(game, delta); }

  inline void Enter(const IGame& game) override { idleDelegate.Enter(game); }

  inline void Exit(const IGame& game) override { idleDelegate.Exit(game); }
};

}
