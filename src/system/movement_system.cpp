#include "movement_system.hpp"

#include <iterator>         // back_inserter
#include <memory_resource>  // monotonic_buffer_resource
#include <vector>           // vector

#include "buffer.hpp"
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

void update_hitbox(level& level,
                   entt::entity entity,
                   comp::movable& movable,
                   comp::hitbox& hitbox,
                   const vector2f& oldPosition)
{
  hitbox::update_position(hitbox, movable.position);
  level.move_aabb(entity, movable.position);

  // TODO don't run movement animation when blocked

  buffer_t<entt::entity, 20> buffer{};
  std::pmr::monotonic_buffer_resource resource{buffer.data(), sizeof buffer};
  std::pmr::vector<entt::entity> candidates{&resource};
  level.query_overlaps(entity, std::back_inserter(candidates));

  for (const auto candidate : candidates) {
    const auto& otherHitbox = level.get<comp::hitbox>(candidate);
    if (hitbox::intersects(hitbox, otherHitbox)) {
      movable.position = oldPosition;
      hitbox::update_position(hitbox, oldPosition);
      level.move_aabb(entity, oldPosition);
      break;
    }
  }
}

}  // namespace

void update_movement(level& level, delta dt)
{
  level.registry().view<comp::movable>().each(
      [&](entt::entity entity, comp::movable& movable) {
        const auto oldPosition = movable.position;
        movable.position += (movable.velocity * static_cast<float>(dt.get()));

        if (auto* hitbox = level.try_get<comp::hitbox>(entity)) {
          update_hitbox(level, entity, movable, *hitbox, oldPosition);
        }

        update_dominant_direction(movable);
        if (auto* drawable = level.try_get<comp::depth_drawable>(entity)) {
          drawable->centerY =
              movable.position.y() + (drawable->dst.height() / 2.0f);
        }
      });
}

}  // namespace wanderer::sys
