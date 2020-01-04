#pragma once
#include "player_state.h"
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

  void draw(const centurion::Renderer& renderer, const Viewport& viewport) const noexcept override;

  void tick(const IWandererCore& core, float delta) override;

  void enter(const IWandererCore& core) override;

  void exit(const IWandererCore& core) override;
};

}
