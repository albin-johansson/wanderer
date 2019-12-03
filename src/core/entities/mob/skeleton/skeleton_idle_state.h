#pragma once
#include "entity_state.h"
#include "entity_state_machine.h"
#include "entity_idle_delegate.h"
#include <SDL_timer.h>

namespace albinjohansson::wanderer {

class SkeletonIdleState : public IEntityState {
 private:
  EntityIdleDelegate idleDelegate;
  Uint32 enterTime = 0;

 public:
  explicit SkeletonIdleState(IEntityStateMachine* parent);

  ~SkeletonIdleState() override;

  void Tick(const IWandererCore& core, float delta) override;

  void Draw(Renderer& renderer, const Viewport& viewport) const override;

  void Enter(const IWandererCore& core) override;

  void Exit(const IWandererCore& core) override;

};

}
