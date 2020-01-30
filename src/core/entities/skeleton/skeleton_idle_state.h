#pragma once
#include "entity_state.h"
#include "wanderer_stdinc.h"
#include "entity_idle_delegate.h"

namespace albinjohansson::wanderer {

class IEntityStateMachine;

class SkeletonIdleState final : public IEntityState {
 private:
  EntityIdleDelegate idleDelegate;
  uint32 enterTime = 0;

 public:
  explicit SkeletonIdleState(IEntityStateMachine* parent);

  ~SkeletonIdleState() final;

  void tick(const IWandererCore& core, float delta) override;

  void draw(const centurion::Renderer& renderer, const Viewport& viewport) const override;

  void enter(const IWandererCore& core) override;

  void exit(const IWandererCore& core) override;

};

}
