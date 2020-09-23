#include "movable_depth_drawables_system.hpp"

#include "depth_drawable.hpp"
#include "movable.hpp"

namespace wanderer::sys {

void update_movable_depth_drawables(entt::registry& registry)
{
  registry.view<comp::movable, comp::depth_drawable>().each(
      [](comp::movable& movable, comp::depth_drawable& drawable) noexcept {
        const auto [x, y] = movable.interpolatedPos;
        drawable.dst.set_x(x);
        drawable.dst.set_y(y);
      });
}

}  // namespace wanderer::sys
