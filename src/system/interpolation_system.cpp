#include "interpolation_system.hpp"

#include "component/movable.hpp"

namespace wanderer::sys {

void update_interpolation(entt::registry& registry, const alpha alpha) noexcept
{
  registry.view<comp::movable>().each([&](comp::movable& movable) noexcept {
    movable.interpolatedPos.set(movable.currentPos);
    movable.interpolatedPos.interpolate(movable.oldPos, alpha.get());
  });
}

}  // namespace wanderer::sys