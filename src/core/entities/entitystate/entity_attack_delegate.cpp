#include "entity_attack_delegate.h"
#include "objects.h"
#include "entity_sheet.h"
#include "entity_draw_delegate.h"

namespace albinjohansson::wanderer {

EntityAttackDelegate::EntityAttackDelegate(IEntityStateMachine* parent) {
  this->parent = Objects::RequireNonNull(parent);
}

EntityAttackDelegate::~EntityAttackDelegate() = default;

void EntityAttackDelegate::Draw(Renderer& renderer, const Viewport& viewport) const {
  auto& entity = parent->GetEntity();
  auto srcX = entity.GetAnimationFrame() * 64;
  auto srcY = EntitySheet::GetSourceY(SOURCE_MELEE_Y, entity.GetDominantDirection());
  EntityDrawDelegate::Draw(renderer, viewport, entity, srcX, srcY);
}

void EntityAttackDelegate::Enter(const IWandererCore& core) {
  IEntity& entity = parent->GetEntity();
  entity.Stop();

  // TODO determine what kind of animation to use from the entity's weapon
  entity.SetAnimationFrameAmount(MELEE_FRAMES);
  entity.SetAnimationFrame(0);
  entity.SetAnimationDelay(65);
  core.PlaySound("swing");
}

void EntityAttackDelegate::Exit(const IWandererCore& core) {}

void EntityAttackDelegate::Tick(const IWandererCore& core, float delta) {
  auto& entity = parent->GetEntity();
  if (entity.IsAnimationDone()) {
    // TODO damage and stuff...
    parent->SetState(EntityStateID::IDLE, core);
  } else {
    entity.UpdateAnimation();
  }
}

}
