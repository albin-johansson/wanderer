#include "skeleton_moving_state.h"
#include "entity_state_machine.h"
#include "random_utils.h"
#include "player.h"
#include "wanderer_core.h"
#include "tile_map.h"
#include <SDL.h>

namespace albinjohansson::wanderer {

SkeletonMovingState::SkeletonMovingState(IEntityStateMachine* parent) : moveDelegate(parent) {}

SkeletonMovingState::~SkeletonMovingState() = default;

void SkeletonMovingState::ChasePlayer(const IWandererCore& core, float distance) {
  auto& entity = moveDelegate.GetParent().GetEntity();

  if (distance <= 75) {
    moveDelegate.GetParent().SetState(EntityStateID::ATTACK, core);
  } else {
    auto entityVelocity = entity.GetVelocity();

    entityVelocity.Set(entity.GetPosition());
    entityVelocity.LookAt(core.GetPlayer().GetPosition(), entity.GetSpeed());

    entity.SetVelocity(entityVelocity);
  }
}

void SkeletonMovingState::Roam(const IWandererCore& core) {
  auto& entity = moveDelegate.GetParent().GetEntity();

  if (SDL_GetTicks() - enterTime >= 1000) {
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

  auto& entity = moveDelegate.GetParent().GetEntity();
  if (core.GetActiveMap().IsBlocked(&entity, delta)) {

    const auto& prevPos = entity.GetPreviousPosition();
    entity.SetX(prevPos.x);
    entity.SetY(prevPos.y);

    // TODO set position of entity to be next to the blocking object

    moveDelegate.GetParent().SetState(EntityStateID::IDLE, core);
    return;
  }

  auto playerPos = core.GetPlayer().GetPosition();

  float distance = entity.GetPosition().DistanceTo(playerPos);
  if (distance <= 400) {
    ChasePlayer(core, distance);
  } else {
    Roam(core);
  }
}

void SkeletonMovingState::Draw(const Renderer& renderer, const Viewport& viewport) const {
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
