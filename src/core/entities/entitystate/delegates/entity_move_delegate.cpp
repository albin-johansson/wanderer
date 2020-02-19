#include "entity_move_delegate.h"

#include "entity.h"
#include "entity_draw_delegate.h"
#include "entity_sheet.h"
#include "entity_state_machine.h"
#include "require.h"
#include "tile_map.h"
#include "wanderer_core.h"

using namespace centurion;
using namespace centurion::video;

namespace albinjohansson::wanderer {

EntityMoveDelegate::EntityMoveDelegate(IEntityStateMachine* parent)
{
  this->parent = Require::not_null(parent);
}

EntityMoveDelegate::~EntityMoveDelegate() = default;

void EntityMoveDelegate::draw(const Renderer& renderer, const Viewport&) const
{
  const auto& entity = parent->get_entity();
  auto srcX =
      entity.get_velocity().is_zero() ? 0 : entity.get_animation_frame() * 64;
  auto srcY = EntitySheet::get_source_y(512, entity.get_dominant_direction());
  EntityDrawDelegate::draw(renderer, entity, srcX, srcY);
}

void EntityMoveDelegate::tick(const IWandererCore&, float delta)
{
  UpdateAnimation();
  UpdatePosition(delta);
}

void EntityMoveDelegate::enter(const IWandererCore&)
{
  auto& entity = parent->get_entity();

  entity.set_animation_frame(0);
  entity.set_animation_frame_amount(9);
  entity.set_animation_delay(60);
}

void EntityMoveDelegate::exit(const IWandererCore&) {}

void EntityMoveDelegate::UpdateAnimation()
{
  parent->get_entity().update_animation();
}

void EntityMoveDelegate::UpdatePosition(float delta)
{
  auto& entity = parent->get_entity();
  auto [velocityX, velocityY] = entity.get_velocity();
  entity.add_x(velocityX * delta);
  entity.add_y(velocityY * delta);
}

IEntityStateMachine& EntityMoveDelegate::get_parent() noexcept
{
  return *parent;
}

}  // namespace albinjohansson::wanderer
