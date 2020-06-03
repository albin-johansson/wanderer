#include "update_movement.h"

#include "animated.h"
#include "movable.h"

namespace wanderer {
namespace {

void update_direction(Movable& movable) noexcept
{
  if (movable.velocity.x > 0) {
    movable.dominantDirection = Direction::Right;
  } else if (movable.velocity.x < 0) {
    movable.dominantDirection = Direction::Left;
  } else {
    if (movable.velocity.y < 0) {
      movable.dominantDirection = Direction::Up;
    } else if (movable.velocity.y > 0) {
      movable.dominantDirection = Direction::Down;
    }
  }
}

}  // namespace

void update_movement(entt::registry& registry, float delta)
{
//  registry.view<Movable>().each([&](Movable& movable) noexcept {
//    movable.oldPos = movable.currentPos;
//    // TODO update hitbox
//    //    movable.hitbox.set_x(m_currPosition.x);
//    //    movable.hitbox.set_y(m_currPosition.y);
//    update_direction(movable);
//    movable.currentPos.add(movable.velocity.x * delta,
//                           movable.velocity.y * delta);
//  });

  const auto entities = registry.view<Movable>();
  for (const auto entity : entities) {
    auto& movable = entities.get<Movable>(entity);

    movable.oldPos = movable.currentPos;
    // TODO update hitbox
    //    movable.hitbox.set_x(m_currPosition.x);
    //    movable.hitbox.set_y(m_currPosition.y);
    update_direction(movable);
    movable.currentPos.add(movable.velocity.x * delta,
                           movable.velocity.y * delta);

    if (auto* animated = registry.try_get<Animated>(entity); animated) {
      animated->animation.tick();
    }
  }
}

}  // namespace wanderer
