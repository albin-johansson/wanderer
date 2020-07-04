#include "movement_system.h"

#include "depth_drawable.h"
#include "hitbox.h"
#include "hitbox_system.h"
#include "movable.h"

using wanderer::comp::DepthDrawable;
using wanderer::comp::Hitbox;
using wanderer::comp::Movable;

namespace wanderer::sys {
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

void update_movement(entt::registry& registry, const delta dt)
{
  registry.view<Movable>(entt::exclude<Hitbox>)
      .each([&registry, dt](const auto entity, Movable& movable) noexcept {
        movable.oldPos = movable.currentPos;
        movable.currentPos.add(movable.velocity.x * dt.get(),
                               movable.velocity.y * dt.get());
        update_direction(movable);

        // FIXME
        if (auto* drawable = registry.try_get<DepthDrawable>(entity);
            drawable) {
          drawable->centerY =
              movable.currentPos.y + (drawable->dst.height() / 2.0f);
        }
      });

  registry.view<Movable, Hitbox>().each(
      [&registry, dt](
          const auto entity, Movable& movable, Hitbox& hitbox) noexcept {

        const auto nextPos = movable.currentPos + (movable.velocity * dt.get());

        // TODO check if the entity will collide with something at next position

        movable.oldPos = movable.currentPos;
        movable.currentPos.add(movable.velocity.x * dt.get(),
                               movable.velocity.y * dt.get());
        update_direction(movable);

        // FIXME
        if (auto* drawable = registry.try_get<DepthDrawable>(entity);
            drawable) {
          drawable->centerY =
              movable.currentPos.y + (drawable->dst.height() / 2.0f);
        }

        hitbox::update_position(hitbox, movable.currentPos);
      });
}

}  // namespace wanderer::sys
