#include "skeleton_idle_state.h"

namespace wanderer::core {

SkeletonIdleState::SkeletonIdleState(IEntityStateMachine* parent)
    : idleDelegate(EntityIdleDelegate(parent)) {}

SkeletonIdleState::~SkeletonIdleState() = default;

void SkeletonIdleState::Tick(const IGame& game, float delta) {

  auto& entity = idleDelegate.GetParent().GetEntity();
  float distance = entity.GetPosition().DistanceTo(game.GetPlayerPosition());

  if (distance <= 400 || (SDL_GetTicks() - enterTime) >= 2000) {
    idleDelegate.GetParent().SetState(EntityStateID::WALK, game);
  }
}

void SkeletonIdleState::Draw(visuals::Renderer& renderer, const Viewport& viewport) const {
  idleDelegate.Draw(renderer, viewport);
}

void SkeletonIdleState::Enter(const IGame& game) {
  idleDelegate.Enter(game);
  enterTime = SDL_GetTicks();
}

void SkeletonIdleState::Exit(const IGame& game) {
  idleDelegate.Exit(game);
}

}
