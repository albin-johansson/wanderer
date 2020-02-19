#pragma once
#include "entity_dying_delegate.h"
#include "entity_state.h"

namespace albinjohansson::wanderer {

class IEntity;

class SkeletonDyingState final : public IEntityState {
 private:
  EntityDyingDelegate dyingDelegate;

 public:
  explicit SkeletonDyingState(IEntity* entity);

  ~SkeletonDyingState() override;

  void draw(const centurion::video::Renderer& renderer,
            const Viewport& viewport) const override;

  void tick(const IWandererCore& core, float delta) override;

  void enter(const IWandererCore& core) override;

  void exit(const IWandererCore& core) override;
};

}  // namespace albinjohansson::wanderer
