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

  void HandleInput(const Input& input, const IWandererCore& core) override;

  inline void Draw(Renderer& renderer, const Viewport& viewport) const noexcept override {
    idleDelegate.Draw(renderer, viewport);
  }

  inline void Tick(const IWandererCore& core, float delta) override { idleDelegate.Tick(core, delta); }

  inline void Enter(const IWandererCore& core) override { idleDelegate.Enter(core); }

  inline void Exit(const IWandererCore& core) override { idleDelegate.Exit(core); }
};

}
