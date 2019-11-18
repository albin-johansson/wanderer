#include "entity_attack_delegate.h"
#include "objects.h"
#include "entity_sheet.h"
#include "entity_draw_delegate.h"

namespace wanderer::core {

EntityAttackDelegate::EntityAttackDelegate(IEntity* entity, IEntityStateMachine* parent) {
  this->entity = Objects::RequireNonNull(entity);
  this->parent = Objects::RequireNonNull(parent);
}

EntityAttackDelegate::~EntityAttackDelegate() = default;

void EntityAttackDelegate::Draw(visuals::Renderer& renderer, const Viewport& viewport) {
  auto srcX = animation.GetIndex() * 64;
  auto srcY = EntitySheet::GetSourceY(0, entity->GetDominantDirection());
  EntityDrawDelegate::Draw(renderer, viewport, *entity, srcX, srcY);
}

void EntityAttackDelegate::Enter() {
  entity->Stop();

  // TODO determine what kind of animation to use from the entity's weapon
  animation.SetNumberOfFrames(7);
  animation.SetFrame(0);
  animation.SetDelay(65);
}

void EntityAttackDelegate::Exit() {}

void EntityAttackDelegate::Tick(float delta) {
  animation.Update();
  if (animation.IsDone()) {

    // TODO damage and stuff...

    parent->Change(EntityStateID::IDLE);
  }
}

}
