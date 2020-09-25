#include "collision_system.hpp"

#include <log.hpp>

#include "aabb_system.hpp"
#include "component/hitbox.hpp"
#include "component/movable.hpp"
#include "hitbox_system.hpp"

namespace wanderer::sys::collision {
namespace {

void fix_positions_after_collision(entt::entity entity,
                                   comp::movable& movable,
                                   const comp::hitbox& fstHitbox,
                                   const comp::hitbox& sndHitbox)
{
  // TODO use movable.dominantDirection?

  //  auto& position = movable.position;
  //  const auto& sndBounds = sndHitbox.bounds;

  switch (movable.dominantDirection) {
    case direction::up: {
      break;
    }

    case direction::down: {
      movable.velocity.set_y(0);
      break;
    }
    case direction::right:
      [[fallthrough]];
    case direction::left: {
      movable.velocity.set_x(0);
      break;
    }
  }
}

}  // namespace

void update(entt::registry& registry)
{
  registry.view<comp::movable, comp::hitbox>().each(
      [&](auto entity, comp::movable& movable, comp::hitbox& hitbox) {
        aabb::query(registry, entity, [&](entt::entity candidate) {
          const auto& otherHitbox = registry.get<comp::hitbox>(candidate);
          if (hitbox::intersects(hitbox, otherHitbox)) {
            /*
             Some thoughts: we only want to block `movable` if it wants to
             move in a blocked direction. It should be free to move in a free
             direction even when it intersects another hitbox.

             */

            // TODO ...

//            if (auto* blocked = registry.try_get<comp::blocked>(entity)) {
//              switch (movable.dominantDirection) {
//                case direction::up:
//                  *blocked &= comp::blocked::up;
//                  break;
//                case direction::right:
//                  *blocked &= comp::blocked::right;
//                  break;
//                case direction::down:
//                  *blocked &= comp::blocked::down;
//                  break;
//                case direction::left:
//                  *blocked &= comp::blocked::left;
//                  break;
//              }

              // was previously blocked

//            } else {
//              // wasn't blocked
//            }

            //            fix_positions_after_collision(entity, movable, hitbox,
            //            otherHitbox);
          }
        });
      });
}

}  // namespace wanderer::sys::collision
