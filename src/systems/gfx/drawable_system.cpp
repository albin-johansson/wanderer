#include "drawable_system.hpp"

#include "components/drawable.hpp"
#include "components/movable.hpp"
#include "components/viewport.hpp"
#include "core/graphics/graphics_context.hpp"
#include "systems/gfx/render_bounds_system.hpp"
#include "wanderer_std.hpp"

namespace wanderer::sys {

void UpdateDrawables(entt::registry& registry)
{
  for (auto&& [entity, movable, drawable] :
       registry.view<const Movable, Drawable>().each()) {
    drawable.dst.set_x(movable.position.x);
    drawable.dst.set_y(movable.position.y);
  }
}

void RenderDrawables(const entt::registry& registry)
{
  const auto& viewport = registry.ctx<ctx::Viewport>();
  auto& graphics = registry.ctx<Ref<GraphicsContext>>().get();

  for (auto&& [entity, drawable] : registry.view<Drawable>().each()) {
    if (cen::intersects(viewport.bounds, drawable.dst)) {
      graphics.Render(drawable.texture, drawable.src, drawable.dst);
    }
  }
}

}  // namespace wanderer::sys
