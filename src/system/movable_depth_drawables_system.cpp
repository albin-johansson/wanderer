#include "movable_depth_drawables_system.hpp"

#include "component/depth_drawable.hpp"
#include "component/movable.hpp"

namespace wanderer::sys {

void update_movable_depth_drawables(entt::registry& registry)
{
  registry.view<comp::movable, comp::depth_drawable>().each(
      [](comp::movable& movable, comp::depth_drawable& drawable) noexcept {
        const auto& pos = movable.interpolatedPos;
        drawable.dst.set_x(pos.x());
        drawable.dst.set_y(pos.y());
      });
}

}  // namespace wanderer::sys
