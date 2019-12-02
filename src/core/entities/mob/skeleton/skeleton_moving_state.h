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

  void ChasePlayer(const ILevel& level, float distance);

  void Roam(const ILevel& level);

  [[nodiscard]] static Direction GetRandomDirection() noexcept;

 public:
  explicit SkeletonMovingState(IEntityStateMachine* parent);

  ~SkeletonMovingState() override;

  void Tick(const ILevel& level, float delta) override;

  void Draw(Renderer& renderer, const Viewport& viewport) const override;

  void Enter(const ILevel& level) override;

  void Exit(const ILevel& level) override;

};

}
