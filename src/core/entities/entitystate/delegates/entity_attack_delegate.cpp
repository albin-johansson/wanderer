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
  this->parent = Require::not_null(parent);
}

EntityAttackDelegate::~EntityAttackDelegate() = default;

void EntityAttackDelegate::draw(const Renderer& renderer, const Viewport&) const {
  const auto& entity = parent->get_entity();
  const auto srcX = entity.get_animation_frame() * 64;
  const auto srcY = EntitySheet::get_source_y(SOURCE_MELEE_Y, entity.get_dominant_direction());
  EntityDrawDelegate::draw(renderer, entity, srcX, srcY);
}

void EntityAttackDelegate::enter(const IWandererCore& core) {
  IEntity& entity = parent->get_entity();
  entity.stop();

  // TODO determine what kind of animation to use from the entity's weapon
  entity.set_animation_frame_amount(MELEE_FRAMES);
  entity.set_animation_frame(0);
  entity.set_animation_delay(65);
  core.play_sound("swing");
}

void EntityAttackDelegate::exit(const IWandererCore&) {}

void EntityAttackDelegate::tick(const IWandererCore& core, float /*delta*/) {
  auto& entity = parent->get_entity();
  if (entity.is_animation_done()) {
    // TODO damage and stuff...
    parent->set_state(EntityStateID::Idle, core);
  } else {
    entity.update_animation();
  }
}

}
