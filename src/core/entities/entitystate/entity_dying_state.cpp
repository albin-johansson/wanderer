#include "entity_dying_state.h"
#include "entity_sheet.h"
#include "objects.h"

namespace wanderer::core {

EntityDyingState::EntityDyingState(IEntity* entity, IEntityStateMachine* parent) {
  this->entity = Objects::RequireNonNull(entity);
  this->parent = Objects::RequireNonNull(parent);
}

EntityDyingState::~EntityDyingState() = default;

void EntityDyingState::Tick(float delta) {
  if (!animation.IsDone()) {
    animation.Update();
  }
}

void EntityDyingState::Draw(visuals::Renderer& renderer, const Viewport& viewport) {
  auto srcX = animation.GetIndex() * 64;
  auto srcY = EntitySheet::GetSourceY(1152, entity->GetDominantDirection());
  drawDelegate.Draw(renderer, viewport, *entity, srcX, srcY);
}

void EntityDyingState::HandleInput(const Input& input) {
}

void EntityDyingState::Enter() {
  animation.SetNumberOfFrames(6);
  animation.SetFrame(0);
  animation.SetDelay(65);
}

void EntityDyingState::Exit() {
}

}
