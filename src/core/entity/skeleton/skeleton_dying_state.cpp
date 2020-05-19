#include "skeleton_dying_state.h"

#include "entity.h"

using namespace centurion;

namespace wanderer {

SkeletonDyingState::SkeletonDyingState(IEntity* entity)
    : m_dyingDelegate{entity}
{}

SkeletonDyingState::~SkeletonDyingState() = default;

void SkeletonDyingState::draw(Renderer& renderer,
                              const Viewport& viewport) const
{
  m_dyingDelegate.draw(renderer, viewport);
}

void SkeletonDyingState::tick(const IWandererCore& core, float delta)
{
  m_dyingDelegate.tick(core, delta);
}

void SkeletonDyingState::enter(const IWandererCore& core)
{
  m_dyingDelegate.enter(core);
}

void SkeletonDyingState::exit(const IWandererCore& core)
{
  m_dyingDelegate.exit(core);
}

}  // namespace wanderer