#include "entity_dying_state.h"

namespace wanderer::core {

EntityDyingState::EntityDyingState(IEntity* entity, IEntityStateMachine* parent)
    : AbstractEntityState(entity, parent) {}

EntityDyingState::~EntityDyingState() = default;

void EntityDyingState::Draw(visuals::Renderer& renderer, const Viewport& viewport) {
  auto srcX = animation.GetIndex() * 64;
  drawDelegate.Draw(renderer, viewport, *entity, srcX, 1280);
}

void EntityDyingState::HandleInput(const Input& input) {
}

void EntityDyingState::Tick(float delta) {
  if (!animation.IsDone()) {
    animation.Update();
  }
}

void EntityDyingState::Enter() {
  animation.SetNumberOfFrames(6);
  animation.SetFrame(0);
  animation.SetDelay(65);
}

void EntityDyingState::Exit() {
}

}
