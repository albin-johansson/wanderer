#include "movement_system.hpp"

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

void update_movable(entt::registry& registry,
                    entt::entity entity,
                    comp::movable& movable,
                    delta dt)
{
  movable.oldPos = movable.currentPos;
  movable.currentPos += (movable.velocity * static_cast<float>(dt.get()));

  update_dominant_direction(movable);

  // FIXME
  if (auto* drawable = registry.try_get<comp::depth_drawable>(entity)) {
    drawable->centerY =
        movable.currentPos.y() + (drawable->dst.height() / 2.0f);
  }
}

}  // namespace

void update_movement(entt::registry& registry, delta dt)
{
  registry.view<comp::movable>().each([&](auto entity, comp::movable& movable) {
    update_movable(registry, entity, movable, dt);

    // TODO check if the entity will collide with something at next
    if (auto* hitbox = registry.try_get<comp::hitbox>(entity)) {
      hitbox::update_position(*hitbox, movable.currentPos);
    }
  });
}

}  // namespace wanderer::sys