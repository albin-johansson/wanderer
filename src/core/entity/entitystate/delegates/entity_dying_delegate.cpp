#include "entity_dying_delegate.h"

#include "entity.h"
#include "entity_draw_delegate.h"
#include "require.h"

using namespace centurion;

namespace wanderer {

EntityDyingDelegate::EntityDyingDelegate(IEntity* entity)
{
  this->m_entity = Require::not_null(entity);
}

EntityDyingDelegate::~EntityDyingDelegate() = default;

void EntityDyingDelegate::draw(Renderer& renderer, const Viewport&) const
{
  // TODO fade entity transparency after finishing animation
  auto srcX = m_entity->get_animation_frame() * 64;
  EntityDrawDelegate::draw(renderer, *m_entity, srcX, 1280);
}

void EntityDyingDelegate::tick(const IWandererCore&, float /*delta*/)
{
  if (!m_entity->is_animation_done()) {
    m_entity->update_animation();
  }
}

void EntityDyingDelegate::enter(const IWandererCore&)
{
  m_entity->set_animation_frame_amount(6);
  m_entity->set_animation_frame(0);
  m_entity->set_animation_delay(65);
}

void EntityDyingDelegate::exit(const IWandererCore&)
{
  // TODO set entity to be dead
}

}  // namespace wanderer
