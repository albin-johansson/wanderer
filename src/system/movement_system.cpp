#include "movement_system.hpp"

#include <iterator>  // back_inserter
#include <vector>    // vector

#include "abby_utils.hpp"
#include "centurion_utils.hpp"
#include "component/hitbox.hpp"
#include "component/movable.hpp"
#include "hitbox_system.hpp"
#include "maybe.hpp"
#include "movable_system.hpp"
#include "stack_resource.hpp"

namespace wanderer::sys::movement {
namespace {

struct next_hitboxes final
{
  maybe<comp::hitbox> horizontal;
  maybe<comp::hitbox> vertical;
};

struct collision_result final
{
  bool horizontal{};
  bool vertical{};
};

[[nodiscard]] auto next_vertical_hitbox(const comp::movable& movable,
                                        const comp::hitbox& hitbox,
                                        const vector2f& oldPosition,
                                        const delta dt) -> maybe<comp::hitbox>
{
  if (movable.velocity.y() != 0) {
    auto next = oldPosition;
    next.set_y(oldPosition.y() +
               (movable.velocity.y() * static_cast<float>(dt.get())));
    return hitbox::with_position(hitbox, next);
  } else {
    return std::nullopt;
  }
}

[[nodiscard]] auto next_horizontal_hitbox(const comp::movable& movable,
                                          const comp::hitbox& hitbox,
                                          const vector2f& oldPosition,
                                          const delta dt) -> maybe<comp::hitbox>
{
  if (movable.velocity.x() != 0) {
    auto next = oldPosition;
    next.set_x(oldPosition.x() +
               (movable.velocity.x() * static_cast<float>(dt.get())));
    return hitbox::with_position(hitbox, next);
  } else {
    return std::nullopt;
  }
}

[[nodiscard]] auto make_next_hitboxes(const comp::movable& movable,
                                      const comp::hitbox& hitbox,
                                      const vector2f& oldPosition,
                                      const delta dt) -> next_hitboxes
{
  return {next_horizontal_hitbox(movable, hitbox, oldPosition, dt),
          next_vertical_hitbox(movable, hitbox, oldPosition, dt)};
}

[[nodiscard]] auto restore_aabb_position(
    const vector2f& previousPos,
    const vector2f& currentBoundsPos,
    const collision_result& collisions) noexcept -> vector2f
{
  if (collisions.horizontal && collisions.vertical) {
    return previousPos;
  } else if (collisions.horizontal) {
    return {previousPos.x(), currentBoundsPos.y()};
  } else /*if (collisions.vertical)*/ {
    return {currentBoundsPos.x(), previousPos.y()};
  }
}

[[nodiscard]] auto update_movable(comp::movable& movable,
                                  const vector2f& oldPosition,
                                  const comp::hitbox& source,
                                  const comp::hitbox& other,
                                  const next_hitboxes& next) -> collision_result
{
  const auto horizontalCollision =
      next.horizontal && hitbox::intersects(*next.horizontal, other);
  const auto verticalCollision =
      next.vertical && hitbox::intersects(*next.vertical, other);

  if (horizontalCollision) {
    movable.position.set_x(oldPosition.x());
    movable.velocity.set_x(0);
  }

  if (verticalCollision) {
    movable.position.set_y(oldPosition.y());
    movable.velocity.set_y(0);
  }

  return {horizontalCollision, verticalCollision};
}

void update_hitbox(level& level,
                   const entt::entity entity,
                   comp::movable& movable,
                   comp::hitbox& hitbox,
                   const vector2f& oldPosition,
                   const delta dt)
{
  hitbox::set_position(hitbox, movable.position);

  const auto oldAabbPos = to_vector(level.get_aabb(entity).m_min);
  level.relocate_aabb(entity, to_vector(hitbox.bounds.position()));

  if (movable.velocity.is_zero()) {
    return;
  }

  stack_resource<sizeof(entt::entity) * 20> resource;
  std::pmr::vector<entt::entity> candidates{resource.get()};
  level.query_collisions(entity, std::back_inserter(candidates));

  const auto next = make_next_hitboxes(movable, hitbox, oldPosition, dt);
  for (const auto candidate : candidates) {
    const auto& other = level.get<comp::hitbox>(candidate);

    const auto collisions =
        update_movable(movable, oldPosition, hitbox, other, next);

    if (collisions.horizontal || collisions.vertical) {
      hitbox::set_position(hitbox, movable.position);
      const auto boundsPos = to_vector(hitbox.bounds.position());
      const auto pos = restore_aabb_position(oldAabbPos, boundsPos, collisions);
      level.relocate_aabb(entity, pos);
    }
  }
}

}  // namespace

void update(level& level, const delta dt)
{
  level.each<comp::movable>(
      [&](const entt::entity entity, comp::movable& movable) {
        const auto oldPosition = movable.position;

        movable.position += (movable.velocity * static_cast<float>(dt.get()));
        movable.dir = movable::dominant_direction(movable);

        if (auto* hitbox = level.try_get<comp::hitbox>(entity)) {
          update_hitbox(level, entity, movable, *hitbox, oldPosition, dt);
        }
      });
}

}  // namespace wanderer::sys::movement
