#include "entity_idle_delegate.h"
#include "entity_state_machine.h"
#include "entity_draw_delegate.h"
#include "entity.h"
#include "entity_sheet.h"
#include "require.h"

using namespace centurion;

namespace albinjohansson::wanderer {

EntityIdleDelegate::EntityIdleDelegate(IEntityStateMachine* parent) {
  this->parent = Require::not_null(parent);
}

EntityIdleDelegate::~EntityIdleDelegate() = default;

void EntityIdleDelegate::draw(const Renderer& renderer, const Viewport&) const {
  IEntity& entity = parent->get_entity();

  const auto srcY = EntitySheet::get_source_y(512, entity.get_dominant_direction());
  EntityDrawDelegate::draw(renderer, entity, 0, srcY);
}

void EntityIdleDelegate::enter(const IWandererCore&) {
  auto& entity = parent->get_entity();

  entity.stop();
  entity.set_animation_frame(0);
}

void EntityIdleDelegate::exit(const IWandererCore&) {}

void EntityIdleDelegate::tick(const IWandererCore&, float /*delta*/) {}

IEntityStateMachine& EntityIdleDelegate::GetParent() noexcept {
  return *parent;
}

}
