#include "entity_idle_delegate.h"
#include "objects.h"
#include "entity_sheet.h"
#include "entity_draw_delegate.h"

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

void EntityIdleDelegate::Enter(const ILevel& level) {}

void EntityIdleDelegate::Exit(const ILevel& level) {}

void EntityIdleDelegate::Tick(const ILevel& level, float delta) {}

}
