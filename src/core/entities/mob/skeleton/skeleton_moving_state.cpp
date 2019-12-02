#include "skeleton_moving_state.h"
#include "random_utils.h"
#include "player.h"
#include "skeleton.h"

namespace albinjohansson::wanderer {

SkeletonMovingState::SkeletonMovingState(IEntityStateMachine* parent) : moveDelegate(parent) {}

SkeletonMovingState::~SkeletonMovingState() = default;

void SkeletonMovingState::ChasePlayer(const ILevel& level, float distance) {
  auto& entity = moveDelegate.GetEntity();

  if (distance <= 75) {
    moveDelegate.GetParent().SetState(EntityStateID::ATTACK, level);
  } else {
    Vector2 entityVelocity = entity.GetVelocity();

    entityVelocity.Set(entity.GetPosition());
    entityVelocity.LookAt(level.GetPlayer().GetPosition(), entity.GetSpeed());

    entity.SetVelocity(entityVelocity);

    // TODO manually set dominant direction
  }
}

void SkeletonMovingState::Roam(const ILevel& level) {
  auto& entity = moveDelegate.GetEntity();

  if (SDL_GetTicks() - enterTime >= Skeleton::HOMING_RANGE) {
    entity.Stop();
    moveDelegate.GetParent().SetState(EntityStateID::IDLE, level);
    return;
  }

  if (entity.GetVelocity().IsZero()) {
    entity.Move(GetRandomDirection());
    if (RandomUtils::GetBool()) {
      entity.Move(GetRandomDirection());
    }
  }
}

Direction SkeletonMovingState::GetRandomDirection() noexcept { // TODO move elsewhere
  return static_cast<Direction>(RandomUtils::GetInt(0, 3));
}

void SkeletonMovingState::Tick(const ILevel& level, float delta) {
  moveDelegate.Tick(level, delta);

  Vector2 playerPos = level.GetPlayer().GetPosition();

  float distance = moveDelegate.GetEntity().GetPosition().DistanceTo(playerPos);
  if (distance <= 400) {
    ChasePlayer(level, distance);
  } else {
    Roam(level);
  }
}

void SkeletonMovingState::Draw(Renderer& renderer, const Viewport& viewport) const {
  moveDelegate.Draw(renderer, viewport);
}

void SkeletonMovingState::Enter(const ILevel& level) {
  moveDelegate.Enter(level);
  enterTime = SDL_GetTicks();
}

void SkeletonMovingState::Exit(const ILevel& level) {
  moveDelegate.Exit(level);
}

}
