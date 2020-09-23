#include "interpolation_system.hpp"

#include "movable.hpp"

namespace wanderer::sys {

void update_interpolation(entt::registry& registry, const alpha alpha) noexcept
{
  registry.view<comp::Movable>().each([&](comp::Movable& movable) noexcept {
    movable.interpolatedPos.set(movable.currentPos);
    movable.interpolatedPos.interpolate(movable.oldPos, alpha.get());
  });
}

}  // namespace wanderer::sys