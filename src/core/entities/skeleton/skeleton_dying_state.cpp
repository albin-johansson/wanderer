#include "skeleton_dying_state.h"

#include "entity.h"

using namespace centurion;

namespace albinjohansson::wanderer {

SkeletonDyingState::SkeletonDyingState(IEntity* entity) : dyingDelegate{entity}
{}

SkeletonDyingState::~SkeletonDyingState() = default;

void SkeletonDyingState::draw(Renderer& renderer,
                              const Viewport& viewport) const
{
  dyingDelegate.draw(renderer, viewport);
}

void SkeletonDyingState::tick(const IWandererCore& core, float delta)
{
  dyingDelegate.tick(core, delta);
}

void SkeletonDyingState::enter(const IWandererCore& core)
{
  dyingDelegate.enter(core);
}

void SkeletonDyingState::exit(const IWandererCore& core)
{
  dyingDelegate.exit(core);
}

}  // namespace albinjohansson::wanderer