#include "interpolation_system.h"

#include "movable.h"

using wanderer::comp::Movable;

namespace wanderer::sys {

void update_interpolation(entt::registry& registry, const alpha alpha) noexcept
{
  registry.view<Movable>().each([&](Movable& movable) noexcept {
    movable.interpolatedPos.set(movable.currentPos);
    movable.interpolatedPos.interpolate(movable.oldPos, alpha.get());
  });
}

}  // namespace wanderer::sys
