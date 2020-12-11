#include "movement_system.hpp"

#include <iterator>  // back_inserter
#include <vector>    // vector

#include "centurion_utils.hpp"
#include "hitbox.hpp"
#include "hitbox_system.hpp"
#include "maybe.hpp"
#include "movable.hpp"
#include "movable_system.hpp"
#include "stack_resource.hpp"

namespace wanderer::sys::movement {
namespace {

[[nodiscard]] auto restore_aabb_position(
    const vector2f& prev,
    const vector2f& curr,
    const hitbox::collision_result& collisions) noexcept -> vector2f
{
  if (collisions.horizontal && collisions.vertical) {
    return prev;
  } else if (collisions.horizontal) {
    return {prev.x, curr.y};
  } else /*if (collisions.vertical)*/ {
    return {curr.x, prev.y};
  }
}

// Checks for collisions, stops the movable if there are collisions
[[nodiscard]] auto update_movable(comp::movable& movable,
                                  const vector2f& oldPosition,
                                  const comp::hitbox& source,
                                  const comp::hitbox& other,
                                  const hitbox::next_hitboxes& next)
    -> hitbox::collision_result
{
  const auto collisions = hitbox::query_collisions(next, other);

  if (collisions.horizontal) {
    movable.position.x = oldPosition.x;
    movable.velocity.x = 0;
  }

  if (collisions.vertical) {
    movable.position.y = oldPosition.y;
    movable.velocity.y = 0;
  }

  return collisions;
}

void update_hitbox(level& level,
                   const entt::entity entity,
                   comp::movable& movable,
                   comp::hitbox& hitbox,
                   const vector2f& oldPosition,
                   const delta dt)
{
  const auto oldAabbPos = level.get_aabb(entity).min();

  hitbox::set_position(hitbox, movable.position);
  level.relocate_aabb(entity, to_vector(hitbox.bounds.position()));

  if (movable.velocity.is_zero()) {
    return;
  }

  stack_resource<sizeof(entt::entity) * 20> resource;
  std::pmr::vector<entt::entity> candidates{resource.get()};
  level.query_collisions(entity, std::back_inserter(candidates));

  const auto next =
      hitbox::make_next_hitboxes(movable, hitbox, oldPosition, dt);

  for (const auto candidate : candidates) {
    const auto collisions = update_movable(movable,
                                           oldPosition,
                                           hitbox,
                                           level.get<comp::hitbox>(candidate),
                                           next);

    if (collisions.horizontal || collisions.vertical) {
      hitbox::set_position(hitbox, movable.position);
      const auto pos =
          restore_aabb_position(oldAabbPos,
                                to_vector(hitbox.bounds.position()),
                                collisions);
      level.relocate_aabb(entity, pos);
    }
  }
}

}  // namespace

void update(level& level, const delta dt)
{
  const auto delta = static_cast<float>(dt.get());
  level.each<comp::movable>(
      [&, delta, dt](const entt::entity entity, comp::movable& movable) {
        const auto oldPosition = movable.position;

        movable.position += (movable.velocity * delta);
        movable.dir = movable::dominant_direction(movable);

        if (auto* hitbox = level.try_get<comp::hitbox>(entity)) {
          update_hitbox(level, entity, movable, *hitbox, oldPosition, dt);
        }
      });
}

}  // namespace wanderer::sys::movement
