#pragma once
#include "player_state.h"
#include "entity_move_delegate.h"

namespace albinjohansson::wanderer {

class IEntityStateMachine;

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
   * @param parent a raw pointer to the parent entity state machine.
   * @throws NullPointerException if the supplied pointer is null.
   * @since 0.1.0
   */
  explicit PlayerMovingState(IEntityStateMachine* parent);

  ~PlayerMovingState() override;

  void HandleInput(const Input& input, const IWandererCore& core) override;

  void Draw(Renderer& renderer, const Viewport& viewport) const noexcept override;

  void Tick(const IWandererCore& core, float delta) override;

  void Enter(const IWandererCore& core) override;

  void Exit(const IWandererCore& core) override;
};

}
