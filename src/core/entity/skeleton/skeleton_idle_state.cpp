#include "skeleton_idle_state.h"

#include <timer.h>

#include "entity_state_machine.h"
#include "player.h"
#include "skeleton.h"
#include "wanderer_core.h"

using namespace centurion;

namespace wanderer {

SkeletonIdleState::SkeletonIdleState(IEntityStateMachine* parent)
    : m_idleDelegate{parent}
{}

SkeletonIdleState::~SkeletonIdleState() = default;

void SkeletonIdleState::tick(const IWandererCore& core, float /*delta*/)
{
  auto& entity = m_idleDelegate.get_parent().get_entity();
  float distance =
      entity.get_position().distance_to(core.get_player().get_position());

  if (distance <= Skeleton::homingRange ||
      (Timer::millis() - m_enterTime) >= 2000) {
    m_idleDelegate.get_parent().set_state(EntityStateID::Walk, core);
  }
}

void SkeletonIdleState::draw(Renderer& renderer, const Viewport& viewport) const
{
  m_idleDelegate.draw(renderer, viewport);
}

void SkeletonIdleState::enter(const IWandererCore& core)
{
  m_idleDelegate.enter(core);
  m_enterTime = Timer::millis();
}

void SkeletonIdleState::exit(const IWandererCore& core)
{
  m_idleDelegate.exit(core);
}

}  // namespace wanderer
