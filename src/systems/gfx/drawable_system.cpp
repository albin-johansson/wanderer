#include "drawable_system.hpp"

#include "common/ref.hpp"
#include "components/ctx/viewport.hpp"
#include "components/gfx/drawable.hpp"
#include "components/physics/movable.hpp"
#include "core/graphics/graphics_context.hpp"
#include "systems/gfx/render_bounds_system.hpp"

namespace wanderer::sys {

void UpdateDrawables(entt::registry& registry)
{
  for (auto&& [entity, movable, drawable] :
       registry.view<const comp::Movable, comp::Drawable>().each())
  {
    drawable.dst.set_x(movable.position.x);
    drawable.dst.set_y(movable.position.y);
  }
}

void RenderDrawables(const entt::registry& registry)
{
  const auto& viewport = registry.ctx<ctx::Viewport>();
  auto& graphics = registry.ctx<ref<GraphicsContext>>().get();

  for (auto&& [entity, drawable] : registry.view<comp::Drawable>().each()) {
    if (cen::intersects(viewport.bounds, drawable.dst)) {
      graphics.render(drawable.texture, drawable.src, drawable.dst);
    }
  }
}

}  // namespace wanderer::sys
