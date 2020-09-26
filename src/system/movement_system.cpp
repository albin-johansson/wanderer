#include "movement_system.hpp"

#include <iterator>         // back_inserter
#include <memory_resource>  // monotonic_buffer_resource
#include <vector>           // vector

#include "buffer.hpp"
#include "component/depth_drawable.hpp"
#include "component/hitbox.hpp"
#include "component/movable.hpp"
#include "hitbox_system.hpp"
#include "movable_system.hpp"

namespace wanderer::sys {
namespace {

void update_position_after_collision(level& level,
                                     entt::entity entity,
                                     comp::movable& movable,
                                     comp::hitbox& hitbox,
                                     const vector2f& oldPosition,
                                     bool collidedVertical,
                                     bool collidedHorizontal)
{
  if (collidedVertical) {
    //    if (const auto dir = get_horizontal_dominant_direction(movable); dir)
    //    {
    //      movable.dominantDirection = *dir;
    //    }
    movable.position.set_y(oldPosition.y());
    movable.velocity.set_y(0);
  }

  if (collidedHorizontal) {
    //    if (const auto dir = get_vertical_dominant_direction(movable); dir) {
    //      movable.dominantDirection = *dir;
    //    }
    movable.position.set_x(oldPosition.x());
    movable.velocity.set_x(0);
  }

  hitbox::update_position(hitbox, movable.position);
  level.move_aabb(entity, movable.position);
}

void update_hitbox(level& level,
                   entt::entity entity,
                   comp::movable& movable,
                   comp::hitbox& hitbox,
                   const vector2f& oldPosition)
{
  hitbox::update_position(hitbox, movable.position);
  level.move_aabb(entity, movable.position);

  buffer_t<entt::entity, 20> buffer{};
  std::pmr::monotonic_buffer_resource resource{buffer.data(), sizeof buffer};
  std::pmr::vector<entt::entity> candidates{&resource};
  level.query_collisions(entity, std::back_inserter(candidates));

  const auto get_next = [&]() -> std::pair<comp::hitbox, comp::hitbox> {
    auto nv = oldPosition;
    nv.set_y(nv.y() + movable.velocity.y());
    const auto nextVertical = hitbox::move_hitbox(hitbox, nv);

    auto nh = oldPosition;
    nh.set_x(nh.x() + movable.velocity.x());
    const auto nextHorizontal = hitbox::move_hitbox(hitbox, nh);

    return {nextVertical, nextHorizontal};
  };
  const auto [nextVertical, nextHorizontal] = get_next();

  for (const auto candidate : candidates) {
    const auto& otherHitbox = level.get<comp::hitbox>(candidate);

    const auto vertical = hitbox::intersects(nextVertical, otherHitbox);
    const auto horizontal = hitbox::intersects(nextHorizontal, otherHitbox);

    if (vertical || horizontal) {
      update_position_after_collision(
          level, entity, movable, hitbox, oldPosition, vertical, horizontal);
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
        movable.dominantDirection = movable::calc_dominant_direction(movable);

        if (auto* hitbox = level.try_get<comp::hitbox>(entity)) {
          update_hitbox(level, entity, movable, *hitbox, oldPosition);
        }

        if (auto* drawable = level.try_get<comp::depth_drawable>(entity)) {
          drawable->centerY = movable.position.y() + drawable->dst.center_y();
        }
      });
}

}  // namespace wanderer::sys
