#include "interpolation_system.h"

#include "movable.h"

namespace wanderer::system {

void update_interpolation(entt::registry& registry, const float alpha) noexcept
{
  registry.view<Movable>().each([&](Movable& movable) noexcept {
    movable.interpolatedPos.set(movable.currentPos);
    movable.interpolatedPos.interpolate(movable.oldPos, alpha);
  });
}

}  // namespace wanderer::system
