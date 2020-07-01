#include "movement_system.h"

#include "depth_drawable.h"
#include "movable.h"

using wanderer::component::DepthDrawable;
using wanderer::component::Movable;

namespace wanderer::system {
namespace {

void update_direction(Movable& movable) noexcept
{
  if (movable.velocity.x > 0) {
    movable.dominantDirection = Direction::Right;
  } else if (movable.velocity.x < 0) {
    movable.dominantDirection = Direction::Left;
  } else {
    if (movable.velocity.y < 0) {
      movable.dominantDirection = Direction::Up;
    } else if (movable.velocity.y > 0) {
      movable.dominantDirection = Direction::Down;
    }
  }
}

}  // namespace

void update_movement(entt::registry& registry, const Delta delta)
{
  registry.view<Movable>().each([&registry, delta](const auto entity,
                                                   Movable& movable) noexcept {
    movable.oldPos = movable.currentPos;
    // TODO update hitbox
    //    movable.hitbox.set_x(m_currPosition.x);
    //    movable.hitbox.set_y(m_currPosition.y);
    update_direction(movable);
    movable.currentPos.add(movable.velocity.x * delta.get(),
                           movable.velocity.y * delta.get());

    // FIXME
    if (auto* drawable = registry.try_get<DepthDrawable>(entity); drawable) {
      drawable->centerY =
          movable.currentPos.y + (drawable->dst.height() / 2.0f);
    }
  });
}

}  // namespace wanderer::system
