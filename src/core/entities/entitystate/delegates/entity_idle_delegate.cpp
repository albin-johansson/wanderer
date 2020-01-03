#include "entity_idle_delegate.h"
#include "entity_state_machine.h"
#include "entity_draw_delegate.h"
#include "entity.h"
#include "entity_sheet.h"
#include "require.h"

namespace albinjohansson::wanderer {

EntityIdleDelegate::EntityIdleDelegate(IEntityStateMachine* parent) {
  this->parent = Require::NotNull(parent);
}

EntityIdleDelegate::~EntityIdleDelegate() = default;

void EntityIdleDelegate::Draw(const Renderer& renderer, const Viewport&) const {
  IEntity& entity = parent->GetEntity();

  const auto srcY = EntitySheet::GetSourceY(512, entity.GetDominantDirection());
  EntityDrawDelegate::Draw(renderer, entity, 0, srcY);
}

void EntityIdleDelegate::Enter(const IWandererCore&) {
  auto& entity = parent->GetEntity();

  entity.Stop();
  entity.SetAnimationFrame(0);
}

void EntityIdleDelegate::Exit(const IWandererCore&) {}

void EntityIdleDelegate::Tick(const IWandererCore&, float /*delta*/) {}

IEntityStateMachine& EntityIdleDelegate::GetParent() noexcept {
  return *parent;
}

}
