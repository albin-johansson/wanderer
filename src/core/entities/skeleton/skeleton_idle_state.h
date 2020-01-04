#pragma once
#include "entity_state.h"
#include "entity_idle_delegate.h"
#include <cstdint>

namespace albinjohansson::wanderer {

class IEntityStateMachine;

class SkeletonIdleState : public IEntityState {
 private:
  EntityIdleDelegate idleDelegate;
  uint32_t enterTime = 0;

 public:
  explicit SkeletonIdleState(IEntityStateMachine* parent);

  ~SkeletonIdleState() override;

  void Tick(const IWandererCore& core, float delta) override;

  void Draw(const centurion::Renderer& renderer, const Viewport& viewport) const override;

  void Enter(const IWandererCore& core) override;

  void Exit(const IWandererCore& core) override;

};

}
