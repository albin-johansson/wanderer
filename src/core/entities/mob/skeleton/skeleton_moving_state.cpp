#include "skeleton_moving_state.h"
#include "random_utils.h"

namespace albinjohansson::wanderer {

SkeletonMovingState::SkeletonMovingState(IEntityStateMachine* parent) : moveDelegate(parent) {}

SkeletonMovingState::~SkeletonMovingState() = default;

void SkeletonMovingState::ChasePlayer(const IGame& game, float distance) {
  auto& entity = moveDelegate.GetEntity();

  if (distance <= 75) {
    moveDelegate.GetParent().SetState(EntityStateID::ATTACK, game);
  } else {
    auto entityVelocity = entity.GetVelocity();

    entityVelocity.Set(entity.GetPosition());
    entityVelocity.LookAt(game.GetPlayerPosition(), entity.GetSpeed());

    entity.SetVelocity(entityVelocity);

    // TODO manually set dominant direction
  }
}

void SkeletonMovingState::Roam(const IGame& game) {
  auto& entity = moveDelegate.GetEntity();

  if (SDL_GetTicks() - enterTime >= 500) {
    entity.Stop();
    moveDelegate.GetParent().SetState(EntityStateID::IDLE, game);
    return;
  }

  if (entity.GetVelocity().IsZero()) {
    entity.Move(GetRandomDirection());
    if (RandomUtils::GetBool()) {
      entity.Move(GetRandomDirection());
    }
  }
}

Direction SkeletonMovingState::GetRandomDirection() const noexcept {
  return static_cast<Direction>(RandomUtils::GetInt(0, 3));
}

void SkeletonMovingState::Tick(const IGame& game, float delta) {
  moveDelegate.Tick(game, delta);
  float distance = moveDelegate.GetEntity().GetPosition().DistanceTo(game.GetPlayerPosition());
  if (distance <= 400) {
    ChasePlayer(game, distance);
  } else {
    Roam(game);
  }
}

void SkeletonMovingState::Draw(Renderer& renderer, const Viewport& viewport) const {
  moveDelegate.Draw(renderer, viewport);
}

void SkeletonMovingState::Enter(const IGame& game) {
  moveDelegate.Enter(game);
  enterTime = SDL_GetTicks();
}

void SkeletonMovingState::Exit(const IGame& game) {
  moveDelegate.Exit(game);
}

}
