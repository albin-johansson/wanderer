#include "entity_idle_delegate.h"

#include "entity.h"
#include "entity_draw_delegate.h"
#include "entity_sheet.h"
#include "entity_state_machine.h"
#include "require.h"

using namespace centurion;

namespace wanderer {

EntityIdleDelegate::EntityIdleDelegate(IEntityStateMachine* parent)
{
  this->m_parent = Require::not_null(parent);
}

EntityIdleDelegate::~EntityIdleDelegate() = default;

void EntityIdleDelegate::draw(Renderer& renderer, const Viewport&) const
{
  const auto& entity = m_parent->get_entity();

  const auto srcY =
      EntitySheet::get_source_y(512, entity.get_dominant_direction());
  EntityDrawDelegate::draw(renderer, entity, 0, srcY);
}

void EntityIdleDelegate::enter(const IWandererCore&)
{
  auto& entity = m_parent->get_entity();

  entity.stop();
  entity.set_animation_frame(0);
}

void EntityIdleDelegate::exit(const IWandererCore&)
{}

void EntityIdleDelegate::tick(const IWandererCore&, float /*delta*/)
{}

IEntityStateMachine& EntityIdleDelegate::get_parent() noexcept
{
  return *m_parent;
}

}  // namespace wanderer
