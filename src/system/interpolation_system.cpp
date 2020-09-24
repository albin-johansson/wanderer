#include "interpolation_system.hpp"

#include "component/movable.hpp"

namespace wanderer::sys {

void update_interpolation(entt::registry& registry, alpha alpha)
{
  registry.view<comp::movable>().each([&](comp::movable& movable) noexcept {
    movable.interpolatedPos = movable.currentPos;
    movable.interpolatedPos.lerp(movable.oldPos, alpha.get());
  });
}

}  // namespace wanderer::sys