#include "entity_attack_state.h"
#include "entity_sheet.h"

using namespace wanderer::visuals;

namespace wanderer::core {

EntityAttackState::EntityAttackState(IEntity* entity, IEntityStateMachine* parent)
    : AbstractEntityState(entity, parent) {}

EntityAttackState::~EntityAttackState() = default;

void EntityAttackState::Draw(visuals::Renderer& renderer, const Viewport& viewport) {
  auto srcX = animation.GetIndex() * 64;
  auto srcY = EntitySheet::GetSourceY(0, entity->GetDominantDirection());
  drawDelegate.Draw(renderer, viewport, *entity, srcX, srcY);
}

void EntityAttackState::HandleInput(const Input& input) {
}

void EntityAttackState::Tick(float delta) {
  animation.Update();
  if (animation.IsDone()) {

    // TODO damage and stuff...

    parent->Change(EntityStateID::IDLE);
  }
}

void EntityAttackState::Enter() {
  entity->Stop();

  // TODO determine what kind of animation to use from the entity's weapon
  animation.SetNumberOfFrames(7);
  animation.SetFrame(0);
  animation.SetDelay(65);

  // TODO play sound here?
}

void EntityAttackState::Exit() {
}

}
