#include "drawable_system.hpp"

#include "depth_drawable.hpp"
#include "movable.hpp"
#include "render_bounds.hpp"
#include "render_bounds_system.hpp"

namespace wanderer::sys {

void update_drawables(entt::registry& registry)
{
  const auto view = registry.view<const comp::movable, comp::depth_drawable>();
  view.each([](const comp::movable& movable, comp::depth_drawable& drawable) noexcept {
    drawable.dst.set_x(movable.position.x);
    drawable.dst.set_y(movable.position.y);
  });
}

void render_drawables(const entt::registry& registry, graphics_context& graphics)
{
  const auto boundsRect = to_rect(registry.ctx<ctx::render_bounds>());
  const auto view = registry.view<const comp::depth_drawable>();
  view.each([&](const comp::depth_drawable& drawable) noexcept {
    if (cen::intersects(boundsRect, drawable.dst))
    {
      graphics.render(drawable.texture, drawable.src, drawable.dst);
    }
  });
}

}  // namespace wanderer::sys
