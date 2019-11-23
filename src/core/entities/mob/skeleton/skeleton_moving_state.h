#pragma once
#include "entity_state.h"
#include "entity_move_delegate.h"
#include "entity_state_machine.h"
#include <SDL_timer.h>

namespace albinjohansson::wanderer {

class SkeletonMovingState final : public IEntityState {
 private:
  EntityMoveDelegate moveDelegate;
  Uint32 enterTime = 0;

  void ChasePlayer(const IGame& game, float distance);

  void Roam(const IGame& game);

  [[nodiscard]] Direction GetRandomDirection() const noexcept;

 public:
  explicit SkeletonMovingState(IEntityStateMachine* parent);

  ~SkeletonMovingState() override;

  void Tick(const IGame& game, float delta) override;

  void Draw(Renderer& renderer, const Viewport& viewport) const override;

  void Enter(const IGame& game) override;

  void Exit(const IGame& game) override;

};

}
