#include "movement_system.hpp"

#include <iterator>  // back_inserter
#include <vector>    // vector

#include <rune/rune.hpp>  // stack_resource

#include "components/hitbox.hpp"
#include "components/movable.hpp"
#include "components/viewport.hpp"
#include "core/utils/centurion_utils.hpp"
#include "systems/physics/direction_system.hpp"
#include "systems/physics/hitbox_system.hpp"

namespace wanderer::sys {
namespace {

[[nodiscard]] auto RestoreAabbPosition(const rune::float2& prev,
                                       const rune::float2& curr,
                                       const CollisionResult& collisions) noexcept
    -> rune::float2
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
[[nodiscard]] auto UpdateMovable(comp::Movable& movable,
                                 const float2& oldPosition,
                                 const comp::Hitbox& other,
                                 const NextHitboxes& next) -> CollisionResult
{
  const auto collisions = QueryCollisions(next, other);

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

[[nodiscard]] auto CheckOutOfBounds(entt::registry& registry,
                                    const NextHitboxes& next,
                                    comp::Movable& movable,
                                    const float2& oldPosition) -> CollisionResult
{
  CollisionResult collisions;

  const auto& viewport = registry.ctx<ctx::Viewport>();
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

void UpdateHitbox(entt::registry& registry,
                  aabb_tree& tree,
                  const entt::entity entity,
                  const float2& oldPosition,
                  const float dt)
{
  const auto oldAabbPos = tree.at(entity).min;

  auto& hitbox = registry.get<comp::Hitbox>(entity);
  auto& movable = registry.get<comp::Movable>(entity);

  SetPosition(hitbox, movable.position);
  tree.set_position(entity, to_rune_vector(hitbox.bounds.position()));

  if (is_zero(movable.velocity)) {
    return;
  }

  rune::stack_resource<sizeof(aabb_tree::key_type) * 20> resource;
  std::pmr::vector<entt::entity> candidates{resource.get()};
  tree.query(entity, std::back_inserter(candidates));

  const auto next = MakeNextHitboxes(movable, hitbox, oldPosition, dt);

  const auto restorePosition = [&](const CollisionResult& collisions) {
    SetPosition(hitbox, movable.position);
    const auto pos = RestoreAabbPosition(oldAabbPos,
                                         to_rune_vector(hitbox.bounds.position()),
                                         collisions);
    tree.set_position(entity, pos);
  };

  {
    const auto collisions = CheckOutOfBounds(registry, next, movable, oldPosition);
    if (collisions.vertical || collisions.horizontal) {
      restorePosition(collisions);
    }
  }

  for (const auto candidate : candidates) {
    const auto collisions =
        UpdateMovable(movable, oldPosition, registry.get<comp::Hitbox>(candidate), next);
    if (collisions.vertical || collisions.horizontal) {
      restorePosition(collisions);
    }
  }
}

}  // namespace

void UpdateMovement(entt::registry& registry, aabb_tree& tree, const float dt)
{
  for (auto&& [entity, movable] : registry.view<comp::Movable>().each()) {
    const auto oldPosition = movable.position;

    movable.position += (movable.velocity * dt);
    movable.dir = GetDominantDirection(movable);

    if (registry.all_of<comp::Hitbox>(entity)) {
      UpdateHitbox(registry, tree, entity, oldPosition, dt);
    }
  }
}

}  // namespace wanderer::sys
