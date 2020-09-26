#include "movable_depth_drawables_system.hpp"

#include "component/depth_drawable.hpp"
#include "component/movable.hpp"

namespace wanderer::sys {

void update_movable_depth_drawables(entt::registry& registry)
{
  registry.view<comp::movable, comp::depth_drawable>().each(
      [](comp::movable& movable, comp::depth_drawable& drawable) noexcept {
        drawable.dst.set_x(movable.position.x());
        drawable.dst.set_y(movable.position.y());
        drawable.centerY =
            movable.position.y() + (drawable.dst.height() / 2.0f);
      });
}

}  // namespace wanderer::sys
