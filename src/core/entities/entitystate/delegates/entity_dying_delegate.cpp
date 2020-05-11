#include "entity_dying_delegate.h"

#include "entity.h"
#include "entity_draw_delegate.h"
#include "require.h"

using namespace centurion;

namespace albinjohansson::wanderer {

EntityDyingDelegate::EntityDyingDelegate(IEntity* entity)
{
  this->entity = Require::not_null(entity);
}

EntityDyingDelegate::~EntityDyingDelegate() = default;

void EntityDyingDelegate::draw(Renderer& renderer, const Viewport&) const
{
  // TODO fade entity transparency after finishing animation
  auto srcX = entity->get_animation_frame() * 64;
  EntityDrawDelegate::draw(renderer, *entity, srcX, 1280);
}

void EntityDyingDelegate::tick(const IWandererCore&, float /*delta*/)
{
  if (!entity->is_animation_done()) {
    entity->update_animation();
  }
}

void EntityDyingDelegate::enter(const IWandererCore&)
{
  entity->set_animation_frame_amount(6);
  entity->set_animation_frame(0);
  entity->set_animation_delay(65);
}

void EntityDyingDelegate::exit(const IWandererCore&)
{
  // TODO set entity to be dead
}

}  // namespace albinjohansson::wanderer
