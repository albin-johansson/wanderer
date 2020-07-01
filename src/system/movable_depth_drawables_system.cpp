#include "movable_depth_drawables_system.h"

#include "depth_drawable.h"
#include "movable.h"

using wanderer::component::DepthDrawable;
using wanderer::component::Movable;

namespace wanderer::system {

void update_movable_depth_drawables(entt::registry& registry)
{
  registry.view<Movable, DepthDrawable>().each(
      [](Movable& movable, DepthDrawable& drawable) noexcept {
        const auto [x, y] = movable.interpolatedPos;
        drawable.dst.set_x(x);
        drawable.dst.set_y(y);
      });
}

}  // namespace wanderer::system
