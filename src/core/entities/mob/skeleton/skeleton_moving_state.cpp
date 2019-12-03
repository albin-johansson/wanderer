#include "skeleton_moving_state.h"
#include "random_utils.h"
#include "player.h"
#include "skeleton.h"

namespace albinjohansson::wanderer {

SkeletonMovingState::SkeletonMovingState(IEntityStateMachine* parent) : moveDelegate(parent) {}

SkeletonMovingState::~SkeletonMovingState() = default;

void SkeletonMovingState::ChasePlayer(const IWandererCore& core, float distance) {
  auto& entity = moveDelegate.GetEntity();

  if (distance <= 75) {
    moveDelegate.GetParent().SetState(EntityStateID::ATTACK, core);
  } else {
    Vector2 entityVelocity = entity.GetVelocity();

    entityVelocity.Set(entity.GetPosition());
    entityVelocity.LookAt(core.GetPlayer().GetPosition(), entity.GetSpeed());

    entity.SetVelocity(entityVelocity);

    // TODO manually set dominant direction
  }
}

void SkeletonMovingState::Roam(const IWandererCore& core) {
  auto& entity = moveDelegate.GetEntity();

  if (SDL_GetTicks() - enterTime >= Skeleton::HOMING_RANGE) {
    entity.Stop();
    moveDelegate.GetParent().SetState(EntityStateID::IDLE, core);
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

void SkeletonMovingState::Tick(const IWandererCore& core, float delta) {
  moveDelegate.Tick(core, delta);

  Vector2 playerPos = core.GetPlayer().GetPosition();

  float distance = moveDelegate.GetEntity().GetPosition().DistanceTo(playerPos);
  if (distance <= 400) {
    ChasePlayer(core, distance);
  } else {
    Roam(core);
  }
}

void SkeletonMovingState::Draw(Renderer& renderer, const Viewport& viewport) const {
  moveDelegate.Draw(renderer, viewport);
}

void SkeletonMovingState::Enter(const IWandererCore& core) {
  moveDelegate.Enter(core);
  enterTime = SDL_GetTicks();
}

void SkeletonMovingState::Exit(const IWandererCore& core) {
  moveDelegate.Exit(core);
}

}
