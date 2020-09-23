#include "movement_system.hpp"

#include "component/depth_drawable.hpp"
#include "component/hitbox.hpp"
#include "component/movable.hpp"
#include "hitbox_system.hpp"

namespace wanderer::sys {
namespace {

void update_direction(comp::movable& movable) noexcept
{
  if (movable.velocity.x() > 0) {
    movable.dominantDirection = Direction::Right;
  } else if (movable.velocity.x() < 0) {
    movable.dominantDirection = Direction::Left;
  } else {
    if (movable.velocity.y() < 0) {
      movable.dominantDirection = Direction::Up;
    } else if (movable.velocity.y() > 0) {
      movable.dominantDirection = Direction::Down;
    }
  }
}

}  // namespace

void update_movement(entt::registry& registry, const delta dt)
{
  registry.view<comp::movable>(entt::exclude<comp::hitbox>)
      .each(
          [&registry, dt](const auto entity, comp::movable& movable) noexcept {
            movable.oldPos = movable.currentPos;
            movable.currentPos += (movable.velocity * dt.get());

            update_direction(movable);

            // FIXME
            if (auto* drawable = registry.try_get<comp::depth_drawable>(entity);
                drawable) {
              drawable->centerY =
                  movable.currentPos.y() + (drawable->dst.height() / 2.0f);
            }
          });

  registry.view<comp::movable, comp::hitbox>().each(
      [&registry, dt](const auto entity,
                      comp::movable& movable,
                      comp::hitbox& hitbox) noexcept {
        const auto nextPos = movable.currentPos + (movable.velocity * dt.get());

        // TODO check if the entity will collide with something at next

        movable.oldPos = movable.currentPos;
        movable.currentPos += (movable.velocity * dt.get());
        update_direction(movable);

        // FIXME
        if (auto* drawable = registry.try_get<comp::depth_drawable>(entity);
            drawable) {
          drawable->centerY =
              movable.currentPos.y() + (drawable->dst.height() / 2.0f);
        }

        hitbox::update_position(hitbox, movable.currentPos);
      });
}

}  // namespace wanderer::sys