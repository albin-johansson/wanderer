#pragma once
#include "entity_state.h"
#include "entity_move_delegate.h"
#include "entity_state_machine.h"
#include "direction.h"
#include <SDL_timer.h>

namespace albinjohansson::wanderer {

class SkeletonMovingState final : public IEntityState {
 private:
  EntityMoveDelegate moveDelegate;
  Uint32 enterTime = 0;

  void ChasePlayer(const IWandererCore& core, float distance);

  void Roam(const IWandererCore& core);

  [[nodiscard]] static Direction GetRandomDirection() noexcept;

 public:
  explicit SkeletonMovingState(IEntityStateMachine* parent);

  ~SkeletonMovingState() override;

  void Tick(const IWandererCore& core, float delta) override;

  void Draw(Renderer& renderer, const Viewport& viewport) const override;

  void Enter(const IWandererCore& core) override;

  void Exit(const IWandererCore& core) override;

};

}
