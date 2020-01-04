#include "entity_attack_delegate.h"
#include "entity_state_machine.h"
#include "require.h"
#include "entity.h"
#include "entity_sheet.h"
#include "entity_draw_delegate.h"
#include "wanderer_core.h"

using namespace centurion;

namespace albinjohansson::wanderer {

EntityAttackDelegate::EntityAttackDelegate(IEntityStateMachine* parent) {
  this->parent = Require::NotNull(parent);
}

EntityAttackDelegate::~EntityAttackDelegate() = default;

void EntityAttackDelegate::Draw(const Renderer& renderer, const Viewport&) const {
  auto& entity = parent->GetEntity();
  auto srcX = entity.GetAnimationFrame() * 64;
  auto srcY = EntitySheet::GetSourceY(SOURCE_MELEE_Y, entity.get_dominant_direction());
  EntityDrawDelegate::Draw(renderer, entity, srcX, srcY);
}

void EntityAttackDelegate::Enter(const IWandererCore& core) {
  IEntity& entity = parent->GetEntity();
  entity.stop();

  // TODO determine what kind of animation to use from the entity's weapon
  entity.SetAnimationFrameAmount(MELEE_FRAMES);
  entity.SetAnimationFrame(0);
  entity.SetAnimationDelay(65);
  core.play_sound("swing");
}

void EntityAttackDelegate::Exit(const IWandererCore&) {}

void EntityAttackDelegate::Tick(const IWandererCore& core, float /*delta*/) {
  auto& entity = parent->GetEntity();
  if (entity.IsAnimationDone()) {
    // TODO damage and stuff...
    parent->SetState(EntityStateID::IDLE, core);
  } else {
    entity.UpdateAnimation();
  }
}

}
