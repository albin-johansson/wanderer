#include "interpolation_system.h"

#include "movable.h"

using wanderer::component::Movable;

namespace wanderer::system {

void update_interpolation(entt::registry& registry, const Alpha alpha) noexcept
{
  registry.view<Movable>().each([&](Movable& movable) noexcept {
    movable.interpolatedPos.set(movable.currentPos);
    movable.interpolatedPos.interpolate(movable.oldPos, alpha.get());
  });
}

}  // namespace wanderer::system
