#include "movement_system.hpp"

#include <log.hpp>

#include "aabb_system.hpp"
#include "component/aabb.hpp"
#include "component/depth_drawable.hpp"
#include "component/hitbox.hpp"
#include "component/movable.hpp"
#include "hitbox_system.hpp"

namespace wanderer::sys {
namespace {

void update_dominant_direction(comp::movable& movable) noexcept
{
  if (movable.velocity.x() > 0) {
    movable.dominantDirection = direction::right;
  } else if (movable.velocity.x() < 0) {
    movable.dominantDirection = direction::left;
  } else {
    if (movable.velocity.y() < 0) {
      movable.dominantDirection = direction::up;
    } else if (movable.velocity.y() > 0) {
      movable.dominantDirection = direction::down;
    }
  }
}

}  // namespace

void update_movement(level& level, delta dt)
{
  auto& registry = level.registry();
  registry.view<comp::movable>().each(
      [&](entt::entity entity, comp::movable& movable) {
        const auto oldPosition = movable.position;
        movable.position += (movable.velocity * static_cast<float>(dt.get()));

        if (auto* hitbox = registry.try_get<comp::hitbox>(entity)) {
          hitbox::update_position(*hitbox, movable.position);
          level.move_aabb(entity, movable.position);

          // TODO don't run movement animation when blocked

          // TODO

          for (const auto candidate : level.query_overlaps(entity)) {
            const auto& otherHitbox = registry.get<comp::hitbox>(candidate);
            if (hitbox::intersects(*hitbox, otherHitbox)) {
              movable.position = oldPosition;
              hitbox::update_position(*hitbox, oldPosition);
              level.move_aabb(entity, oldPosition);
            }
          }
        }

        update_dominant_direction(movable);
        if (auto* drawable = registry.try_get<comp::depth_drawable>(entity)) {
          drawable->centerY =
              movable.position.y() + (drawable->dst.height() / 2.0f);
        }
      });
}

}  // namespace wanderer::sys
