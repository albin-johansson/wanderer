#include "interpolation.h"

#include "movable.h"

namespace wanderer {

void interpolate(entt::registry& registry, const f32 alpha)
{
  registry.view<Movable>().each([&](Movable& movable) noexcept {
    movable.interpolatedPos.set(movable.currentPos);
    movable.interpolatedPos.interpolate(movable.oldPos, alpha);
  });
}

}  // namespace wanderer
