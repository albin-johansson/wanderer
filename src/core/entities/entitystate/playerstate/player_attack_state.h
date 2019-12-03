#pragma once
#include "player_state.h"
#include "entity.h"
#include "entity_state_machine.h"
#include "entity_attack_delegate.h"

namespace albinjohansson::wanderer {

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
   * @param parent a pointer to the parent state machine.
   * @throws NullPointerException if the supplied pointer is null.
   * @since 0.1.0
   */
  explicit PlayerAttackState(IEntityStateMachine* parent);

  ~PlayerAttackState() override;

  void HandleInput(const Input& input, const IWandererCore& core) override;

  inline void Draw(Renderer& renderer, const Viewport& viewport) const override {
    attackDelegate.Draw(renderer, viewport);
  }

  inline void Tick(const IWandererCore& core, float delta) override { attackDelegate.Tick(core, delta); }

  inline void Enter(const IWandererCore& core) override { attackDelegate.Enter(core); }

  inline void Exit(const IWandererCore& core) override { attackDelegate.Exit(core); }

};

}
