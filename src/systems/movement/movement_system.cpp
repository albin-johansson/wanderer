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

namespace wanderer::sys {
namespace {

[[nodiscard]] auto restore_aabb_position(const float2& prev,
                                         const float2& curr,
                                         const collision_result& collisions) noexcept
    -> float2
{
  if (collisions.horizontal && collisions.vertical)
  {
    return prev;
  }
  else if (collisions.horizontal)
  {
    return {prev.x, curr.y};
  }
  else /*if (collisions.vertical)*/
  {
    return {curr.x, prev.y};
  }
}

// Checks for collisions, stops the movable if there are collisions
[[nodiscard]] auto update_movable(comp::movable& movable,
                                  const float2& oldPosition,
                                  const comp::hitbox& source,
                                  const comp::hitbox& other,
                                  const next_hitboxes& next) -> collision_result
{
  const auto collisions = query_collisions(next, other);

  if (collisions.horizontal)
  {
    movable.position.x = oldPosition.x;
    movable.velocity.x = 0;
  }

  if (collisions.vertical)
  {
    movable.position.y = oldPosition.y;
    movable.velocity.y = 0;
  }

  return collisions;
}

[[nodiscard]] auto check_out_of_bounds(level& level,
                                       const next_hitboxes& next,
                                       const entt::entity entity,
                                       comp::movable& movable,
                                       comp::hitbox& hitbox,
                                       const float2& oldPosition,
                                       const float2& oldAabbPos) -> collision_result
{
  collision_result collisions;

  const auto& viewport = level.get<comp::viewport>(level.viewport());
  if (next.horizontal)
  {
    if ((next.horizontal->bounds.x() <= 0) ||
        (next.horizontal->bounds.max_x() >= viewport.levelSize.width))
    {
      movable.position.x = oldPosition.x;
      movable.velocity.x = 0;
      collisions.horizontal = true;
    }
  }

  if (next.vertical)
  {
    if ((next.vertical->bounds.y() <= 0) ||
        (next.vertical->bounds.max_y() >= viewport.levelSize.height))
    {
      movable.position.y = oldPosition.y;
      movable.velocity.y = 0;
      collisions.vertical = true;
    }
  }

  return collisions;
}

void update_hitbox(level& level,
                   const entt::entity entity,
                   comp::movable& movable,
                   comp::hitbox& hitbox,
                   const float2& oldPosition,
                   const delta_t dt)
{
  const auto oldAabbPos = level.get_aabb(entity).min();

  set_position(hitbox, movable.position);
  level.relocate_aabb(entity, to_vector(hitbox.bounds.position()));

  if (movable.velocity.is_zero())
  {
    return;
  }

  stack_resource<sizeof(entt::entity) * 20> resource;
  std::pmr::vector<entt::entity> candidates{resource.get()};
  level.query_collisions(entity, std::back_inserter(candidates));

  const auto next = make_next_hitboxes(movable, hitbox, oldPosition, dt);

  const auto restorePosition = [&](const collision_result& collisions) {
    set_position(hitbox, movable.position);
    const auto pos = restore_aabb_position(oldAabbPos,
                                           to_vector(hitbox.bounds.position()),
                                           collisions);
    level.relocate_aabb(entity, pos);
  };

  {
    const auto collisions = check_out_of_bounds(level,
                                                next,
                                                entity,
                                                movable,
                                                hitbox,
                                                oldPosition,
                                                oldAabbPos);
    if (collisions.vertical || collisions.horizontal)
    {
      restorePosition(collisions);
    }
  }

  for (const auto candidate : candidates)
  {
    const auto collisions = update_movable(movable,
                                           oldPosition,
                                           hitbox,
                                           level.get<comp::hitbox>(candidate),
                                           next);
    if (collisions.vertical || collisions.horizontal)
    {
      restorePosition(collisions);
    }
  }
}

}  // namespace

void update_movement(level& level, const delta_t dt)
{
  level.each<comp::movable>([&](const entt::entity entity, comp::movable& movable) {
    const auto oldPosition = movable.position;

    movable.position += (movable.velocity * dt);
    movable.dir = dominant_direction(movable);

    if (auto* hitbox = level.try_get<comp::hitbox>(entity))
    {
      update_hitbox(level, entity, movable, *hitbox, oldPosition, dt);
    }
  });
}

}  // namespace wanderer::sys
