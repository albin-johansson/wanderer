#include "skeleton_moving_state.h"

#include <timer.h>

#include "entity_state_machine.h"
#include "player.h"
#include "random_utils.h"
#include "tile_map.h"
#include "wanderer_core.h"

using namespace centurion;

namespace albinjohansson::wanderer {

SkeletonMovingState::SkeletonMovingState(IEntityStateMachine* parent)
    : moveDelegate(parent)
{}

SkeletonMovingState::~SkeletonMovingState() = default;

void SkeletonMovingState::ChasePlayer(const IWandererCore& core, float distance)
{
  auto& entity = moveDelegate.get_parent().get_entity();

  if (distance <= 75) {
    moveDelegate.get_parent().set_state(EntityStateID::Attack, core);
  } else {
    auto entityVelocity = entity.get_velocity();

    entityVelocity.set(entity.get_position());
    entityVelocity.look_at(core.get_player().get_position(),
                           entity.get_speed());

    entity.set_velocity(entityVelocity);
  }
}

void SkeletonMovingState::Roam(const IWandererCore& core)
{
  auto& entity = moveDelegate.get_parent().get_entity();

  if (Timer::millis() - enterTime >= 1000) {
    moveDelegate.get_parent().set_state(EntityStateID::Idle, core);
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
  moveDelegate.tick(core, delta);

  auto& entity = moveDelegate.get_parent().get_entity();
  if (core.get_active_map().is_blocked(&entity, delta)) {
    const auto& prevPos = entity.get_previous_position();
    entity.set_x(prevPos.x);
    entity.set_y(prevPos.y);

    // TODO set position of entity to be next to the blocking object

    moveDelegate.get_parent().set_state(EntityStateID::Idle, core);
    return;
  }

  auto playerPos = core.get_player().get_position();

  float distance = entity.get_position().distance_to(playerPos);
  if (distance <= 400) {
    ChasePlayer(core, distance);
  } else {
    Roam(core);
  }
}

void SkeletonMovingState::draw(Renderer& renderer,
                               const Viewport& viewport) const
{
  moveDelegate.draw(renderer, viewport);
}

void SkeletonMovingState::enter(const IWandererCore& core)
{
  moveDelegate.enter(core);
  enterTime = Timer::millis();
}

void SkeletonMovingState::exit(const IWandererCore& core)
{
  moveDelegate.exit(core);
}

}  // namespace albinjohansson::wanderer
