#include "movement_system.hpp"

#include <iterator>  // back_inserter
#include <vector>    // vector

#include "buffer.hpp"
#include "component/depth_drawable.hpp"
#include "component/hitbox.hpp"
#include "component/movable.hpp"
#include "hitbox_system.hpp"
#include "movable_system.hpp"
#include "stack_resource.hpp"

namespace wanderer::sys {
namespace {

[[nodiscard]] auto get_next_hitboxes(const comp::movable& movable,
                                     const comp::hitbox& hitbox,
                                     const vector2f& oldPosition)
    -> std::pair<comp::hitbox, comp::hitbox>
{
  auto nextVPos = oldPosition;
  nextVPos.set_y(nextVPos.y() + movable.velocity.y());
  const auto nextVertical = hitbox::move_hitbox(hitbox, nextVPos);

  auto nextHPos = oldPosition;
  nextHPos.set_x(nextHPos.x() + movable.velocity.x());
  const auto nextHorizontal = hitbox::move_hitbox(hitbox, nextHPos);

  return {nextVertical, nextHorizontal};
}

void update_hitbox(level& level,
                   entt::entity entity,
                   comp::movable& movable,
                   comp::hitbox& hitbox,
                   const vector2f& oldPosition)
{
  hitbox::update_position(hitbox, movable.position);
  level.relocate_aabb(entity, movable.position);

  stack_resource<sizeof(entt::entity) * 20> resource;
  std::pmr::vector<entt::entity> candidates{resource.get()};
  level.query_collisions(entity, std::back_inserter(candidates));

  const auto [nextVertical, nextHorizontal] =
      get_next_hitboxes(movable, hitbox, oldPosition);

  for (const auto candidate : candidates) {
    const auto& otherHitbox = level.get<comp::hitbox>(candidate);

    const auto vCollision = hitbox::intersects(nextVertical, otherHitbox);
    const auto hCollision = hitbox::intersects(nextHorizontal, otherHitbox);

    if (vCollision || hCollision) {
      if (vCollision) {
        movable.position.set_y(oldPosition.y());
        movable.velocity.set_y(0);
      }

      if (hCollision) {
        movable.position.set_x(oldPosition.x());
        movable.velocity.set_x(0);
      }

      hitbox::update_position(hitbox, movable.position);
      level.relocate_aabb(entity, movable.position);

      break;
    }
  }
}

}  // namespace

void update_movement(level& level, delta dt)
{
  level.each<comp::movable>([&](entt::entity entity, comp::movable& movable) {
    const auto oldPosition = movable.position;

    movable.position += (movable.velocity * static_cast<float>(dt.get()));
    movable.dominantDirection = movable::calc_dominant_direction(movable);

    if (auto* hitbox = level.try_get<comp::hitbox>(entity)) {
      update_hitbox(level, entity, movable, *hitbox, oldPosition);
    }
  });
}

}  // namespace wanderer::sys
