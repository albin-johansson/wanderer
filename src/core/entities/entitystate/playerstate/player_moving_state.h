#pragma once
#include "player_state.h"
#include "entity_state_machine.h"
#include "entity_move_delegate.h"
#include "entity.h"

namespace albinjohansson::wanderer {

/**
 * The PlayerMovingState class is an implementation of the IPlayerState interface that represents
 * the state of the player when moving.
 *
 * @see IPlayerState
 * @since 0.1.0
 */
class PlayerMovingState final : public IPlayerState {
 private:
  IEntityStateMachine* parent = nullptr;
  EntityMoveDelegate moveDelegate;
  bool areMoveKeysDown = false;

  void CheckPressed(const Input& input);

  void CheckReleased(const Input& input);

 public:
  /**
   * @param parent a pointer to the parent entity state machine.
   * @throws NullPointerException if the supplied pointer is null.
   * @since 0.1.0
   */
  explicit PlayerMovingState(IEntityStateMachine* parent);

  ~PlayerMovingState() override;

  void HandleInput(const Input& input, const ILevel& level) override;

  inline void Draw(Renderer& renderer, const Viewport& viewport) const noexcept override {
    moveDelegate.Draw(renderer, viewport);
  }

  inline void Tick(const ILevel& level, float delta) override { moveDelegate.Tick(level, delta); }

  inline void Enter(const ILevel& level) override { moveDelegate.Enter(level); }

  inline void Exit(const ILevel& level) override { moveDelegate.Exit(level); }
};

}
