#include "skeleton_moving_state.h"

#include <timer.h>

#include "entity_state_machine.h"
#include "player.h"
#include "random_utils.h"
#include "tile_map.h"
#include "wanderer_core.h"

using namespace centurion;

namespace wanderer {

SkeletonMovingState::SkeletonMovingState(IEntityStateMachine* parent)
    : m_moveDelegate(parent)
{}

SkeletonMovingState::~SkeletonMovingState() = default;

void SkeletonMovingState::chase_player(const IWandererCore& core,
                                       float distance)
{
  auto& entity = m_moveDelegate.get_parent().get_entity();

  if (distance <= 75) {
    m_moveDelegate.get_parent().set_state(EntityStateID::Attack, core);
  } else {
    auto entityVelocity = entity.get_velocity();

    entityVelocity.set(entity.get_position());
    entityVelocity.look_at(core.get_player().get_position(),
                           entity.get_speed());

    entity.set_velocity(entityVelocity);
  }
}

void SkeletonMovingState::roam(const IWandererCore& core)
{
  auto& entity = m_moveDelegate.get_parent().get_entity();

  if (Timer::millis() - m_enterTime >= 1000) {
    m_moveDelegate.get_parent().set_state(EntityStateID::Idle, core);
    return;
  }

  if (entity.get_velocity().is_zero()) {
    entity.move(get_random_direction());
    if (RandomUtils::get_bool()) {
      entity.move(get_random_direction());
    }
  }
}

void SkeletonMovingState::tick(const IWandererCore& core, float delta)
{
  m_moveDelegate.tick(core, delta);

  auto& entity = m_moveDelegate.get_parent().get_entity();
  if (core.get_active_map().is_blocked(&entity, delta)) {
    const auto& prevPos = entity.get_previous_position();
    entity.set_x(prevPos.x);
    entity.set_y(prevPos.y);

    // TODO set position of entity to be next to the blocking object

    m_moveDelegate.get_parent().set_state(EntityStateID::Idle, core);
    return;
  }

  auto playerPos = core.get_player().get_position();

  float distance = entity.get_position().distance_to(playerPos);
  if (distance <= 400) {
    chase_player(core, distance);
  } else {
    roam(core);
  }
}

void SkeletonMovingState::draw(Renderer& renderer,
                               const Viewport& viewport) const
{
  m_moveDelegate.draw(renderer, viewport);
}

void SkeletonMovingState::enter(const IWandererCore& core)
{
  m_moveDelegate.enter(core);
  m_enterTime = Timer::millis();
}

void SkeletonMovingState::exit(const IWandererCore& core)
{
  m_moveDelegate.exit(core);
}

}  // namespace wanderer
