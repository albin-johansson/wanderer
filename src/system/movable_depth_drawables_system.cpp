#include "movable_depth_drawables_system.hpp"

#include "depth_drawable.hpp"
#include "movable.hpp"

namespace wanderer::sys {

void update_movable_depth_drawables(entt::registry& registry)
{
  registry.view<comp::Movable, comp::DepthDrawable>().each(
      [](comp::Movable& movable, comp::DepthDrawable& drawable) noexcept {
        const auto [x, y] = movable.interpolatedPos;
        drawable.dst.set_x(x);
        drawable.dst.set_y(y);
      });
}

}  // namespace wanderer::sys
