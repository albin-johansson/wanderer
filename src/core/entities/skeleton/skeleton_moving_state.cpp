#include "skeleton_moving_state.h"
#include "entity_state_machine.h"
#include "random_utils.h"
#include "player.h"
#include "wanderer_core.h"
#include "tile_map.h"
#include <SDL.h>

using namespace centurion;

namespace albinjohansson::wanderer {

SkeletonMovingState::SkeletonMovingState(IEntityStateMachine* parent) : moveDelegate(parent) {}

SkeletonMovingState::~SkeletonMovingState() = default;

void SkeletonMovingState::ChasePlayer(const IWandererCore& core, float distance) {
  auto& entity = moveDelegate.GetParent().get_entity();

  if (distance <= 75) {
    moveDelegate.GetParent().set_state(EntityStateID::Attack, core);
  } else {
    auto entityVelocity = entity.get_velocity();

    entityVelocity.set(entity.get_position());
    entityVelocity.look_at(core.get_player().get_position(), entity.get_speed());

    entity.set_velocity(entityVelocity);
  }
}

void SkeletonMovingState::Roam(const IWandererCore& core) {
  auto& entity = moveDelegate.GetParent().get_entity();

  if (SDL_GetTicks() - enterTime >= 1000) {
    moveDelegate.GetParent().set_state(EntityStateID::Idle, core);
    return;
  }

  if (entity.get_velocity().is_zero()) {
    entity.move(get_random_direction());
    if (RandomUtils::get_bool()) {
      entity.move(get_random_direction());
    }
  }
}

void SkeletonMovingState::tick(const IWandererCore& core, float delta) {
  moveDelegate.tick(core, delta);

  auto& entity = moveDelegate.GetParent().get_entity();
  if (core.get_active_map().is_blocked(&entity, delta)) {

    const auto& prevPos = entity.get_previous_position();
    entity.set_x(prevPos.x);
    entity.set_y(prevPos.y);

    // TODO set position of entity to be next to the blocking object

    moveDelegate.GetParent().set_state(EntityStateID::Idle, core);
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

void SkeletonMovingState::draw(const Renderer& renderer, const Viewport& viewport) const {
  moveDelegate.draw(renderer, viewport);
}

void SkeletonMovingState::enter(const IWandererCore& core) {
  moveDelegate.enter(core);
  enterTime = SDL_GetTicks();
}

void SkeletonMovingState::exit(const IWandererCore& core) {
  moveDelegate.exit(core);
}

}
