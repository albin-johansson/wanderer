#pragma once
#include "entity_state.h"
#include "entity_state_machine.h"
#include "entity_idle_delegate.h"
#include <SDL_timer.h>

namespace wanderer::core {

class SkeletonIdleState : public IEntityState {
 private:
  EntityIdleDelegate idleDelegate;
  Uint32 enterTime = 0;

 public:
  explicit SkeletonIdleState(IEntityStateMachine* parent);

  ~SkeletonIdleState() override;

  void Tick(const IGame& game, float delta) override;

  void Draw(visuals::Renderer& renderer, const Viewport& viewport) const override;

  void Enter(const IGame& game) override;

  void Exit(const IGame& game) override;

};

}
