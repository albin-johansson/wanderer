#pragma once
#include "player_state.h"
#include "entity.h"
#include "entity_state_machine.h"
#include "entity_dying_delegate.h"

namespace albinjohansson::wanderer {

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
   * @throws NullPointerException if the supplied pointer is null.
   * @since 0.1.0
   */
  explicit PlayerDyingState(IEntity* entity);

  ~PlayerDyingState() override;

  void HandleInput(const Input& input, const ILevel& level) override;

  inline void Draw(Renderer& renderer, const Viewport& viewport) const override {
    dyingDelegate.Draw(renderer, viewport);
  }

  inline void Tick(const ILevel& level, float delta) override { dyingDelegate.Tick(level, delta); }

  inline void Enter(const ILevel& level) override { dyingDelegate.Enter(level); }

  // TODO level over stuff
  inline void Exit(const ILevel& level) override { dyingDelegate.Exit(level); }
};

}
