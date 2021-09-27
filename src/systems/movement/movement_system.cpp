#include "movement_system.hpp"

#include <iterator>             // back_inserter
#include <rune/everything.hpp>  // stack_resource
#include <vector>               // vector

#include "components/ctx/viewport.hpp"
#include "components/hitbox.hpp"
#include "components/movable.hpp"
#include "core/utils/centurion_utils.hpp"
#include "systems/movement/direction_system.hpp"
#include "systems/movement/hitbox_system.hpp"

namespace wanderer::sys {
namespace {

[[nodiscard]] auto restore_aabb_position(const float2 prev,
                                         const float2 curr,
                                         const collision_result& collisions) noexcept
    -> float2
{
  if (collisions.horizontal && collisions.vertical) {
    return prev;
  }
  else if (collisions.horizontal) {
    return {prev.x, curr.y};
  }
  else /*if (collisions.vertical)*/ {
    return {curr.x, prev.y};
  }
}

// Checks for collisions, stops the movable if there are collisions
[[nodiscard]] auto update_movable(comp::movable& movable,
                                  const float2 oldPosition,
                                  const comp::hitbox& other,
                                  const next_hitboxes& next) -> collision_result
{
  const auto collisions = query_collisions(next, other);

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

[[nodiscard]] auto check_out_of_bounds(entt::registry& registry,
                                       const next_hitboxes& next,
                                       comp::movable& movable,
                                       const float2 oldPosition) -> collision_result
{
  collision_result collisions;

  const auto& viewport = registry.ctx<ctx::viewport>();
  if (next.horizontal) {
    if ((next.horizontal->bounds.x() <= 0) ||
        (next.horizontal->bounds.max_x() >= viewport.level_size.width))
    {
      movable.position.x = oldPosition.x;
      movable.velocity.x = 0;
      collisions.horizontal = true;
    }
  }

  if (next.vertical) {
    if ((next.vertical->bounds.y() <= 0) ||
        (next.vertical->bounds.max_y() >= viewport.level_size.height))
    {
      movable.position.y = oldPosition.y;
      movable.velocity.y = 0;
      collisions.vertical = true;
    }
  }

  return collisions;
}

void update_hitbox(entt::registry& registry,
                   aabb_tree& tree,
                   const entt::entity entity,
                   const float2 oldPosition,
                   const float dt)
{
  const auto oldAabbPos = tree.at(entity).min;

  auto& hitbox = registry.get<comp::hitbox>(entity);
  auto& movable = registry.get<comp::movable>(entity);

  set_position(hitbox, movable.position);
  tree.set_position(entity, to_vector(hitbox.bounds.position()));

  if (movable.velocity.is_zero()) {
    return;
  }

  rune::stack_resource<sizeof(aabb_tree::key_type) * 20> resource;
  std::pmr::vector<entt::entity> candidates{resource.get()};
  tree.query(entity, std::back_inserter(candidates));

  const auto next = make_next_hitboxes(movable, hitbox, oldPosition, dt);

  const auto restorePosition = [&](const collision_result& collisions) {
    set_position(hitbox, movable.position);
    const auto pos = restore_aabb_position(oldAabbPos,
                                           to_vector(hitbox.bounds.position()),
                                           collisions);
    tree.set_position(entity, pos);
  };

  {
    const auto collisions = check_out_of_bounds(registry, next, movable, oldPosition);
    if (collisions.vertical || collisions.horizontal) {
      restorePosition(collisions);
    }
  }

  for (const auto candidate : candidates) {
    const auto collisions =
        update_movable(movable, oldPosition, registry.get<comp::hitbox>(candidate), next);
    if (collisions.vertical || collisions.horizontal) {
      restorePosition(collisions);
    }
  }
}

}  // namespace

void update_movement(entt::registry& registry, aabb_tree& tree, const float dt)
{
  for (auto&& [entity, movable] : registry.view<comp::movable>().each()) {
    const auto oldPosition = movable.position;

    movable.position += (movable.velocity * dt);
    movable.dir = dominant_direction(movable);

    if (registry.all_of<comp::hitbox>(entity)) {
      update_hitbox(registry, tree, entity, oldPosition, dt);
    }
  }
}

}  // namespace wanderer::sys
