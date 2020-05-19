#pragma once
#include "entity_idle_delegate.h"
#include "entity_state.h"
#include "wanderer_stdinc.h"

namespace wanderer {

class IEntityStateMachine;

class SkeletonIdleState final : public IEntityState {
 public:
  explicit SkeletonIdleState(IEntityStateMachine* parent);

  ~SkeletonIdleState() final;

  void tick(const IWandererCore& core, float delta) override;

  void draw(ctn::Renderer& renderer, const Viewport& viewport) const override;

  void enter(const IWandererCore& core) override;

  void exit(const IWandererCore& core) override;

 private:
  EntityIdleDelegate m_idleDelegate;
  uint32 m_enterTime = 0;
};

}  // namespace wanderer
