#include "entity_idle_delegate.h"
#include "entity_state_machine.h"
#include "entity_draw_delegate.h"
#include "entity.h"
#include "entity_sheet.h"
#include "objects.h"

namespace albinjohansson::wanderer {

EntityIdleDelegate::EntityIdleDelegate(IEntityStateMachine* parent) {
  this->parent = Objects::RequireNonNull(parent);
}

EntityIdleDelegate::~EntityIdleDelegate() = default;

void EntityIdleDelegate::Draw(Renderer& renderer, const Viewport& viewport) const {
  IEntity& entity = parent->GetEntity();

  float srcY = EntitySheet::GetSourceY(512, entity.GetDominantDirection());
  EntityDrawDelegate::Draw(renderer, viewport, entity, 0, srcY);
}

void EntityIdleDelegate::Enter(const IWandererCore& core) {
  parent->GetEntity().Stop();
}

void EntityIdleDelegate::Exit(const IWandererCore& core) {}

void EntityIdleDelegate::Tick(const IWandererCore& core, float delta) {}

IEntityStateMachine& EntityIdleDelegate::GetParent() noexcept {
  return *parent;
}

}
