#include "drawable_system.hpp"

#include "components/ctx/viewport.hpp"
#include "components/gfx/depth_drawable.hpp"
#include "components/physics/movable.hpp"
#include "systems/graphics/render_bounds_system.hpp"

namespace wanderer::sys {

void update_drawables(entt::registry& registry)
{
  for (auto&& [entity, movable, drawable] :
       registry.view<const comp::movable, comp::depth_drawable>().each())
  {
    drawable.dst.set_x(movable.position.x);
    drawable.dst.set_y(movable.position.y);
  }
}

void render_drawables(const entt::registry& registry, graphics_context& graphics)
{
  const auto& viewport = registry.ctx<ctx::viewport>();

  for (auto&& [entity, drawable] : registry.view<comp::depth_drawable>().each()) {
    if (cen::intersects(viewport.bounds, drawable.dst)) {
      graphics.render(drawable.texture, drawable.src, drawable.dst);
    }
  }
}

}  // namespace wanderer::sys
