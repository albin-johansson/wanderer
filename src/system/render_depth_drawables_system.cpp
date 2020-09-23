#include "render_depth_drawables_system.hpp"

#include "depth_drawable.hpp"
#include "hitbox.hpp"

namespace wanderer::sys {

void render_depth_drawables(entt::registry& registry, cen::renderer& renderer)
{
  // TODO could have movables signal events when they have moved to check if
  //  they are within the viewport bounds and therefore should be rendered,
  //  this would make it possible to have a "InBounds" component

  registry.sort<comp::DepthDrawable>(
      [](const comp::DepthDrawable& lhs,
         const comp::DepthDrawable& rhs) noexcept {
        return lhs.depth < rhs.depth ||
               (rhs.depth >= lhs.depth && lhs.centerY < rhs.centerY);
      },
      entt::insertion_sort{});

  registry.view<comp::DepthDrawable>().each(
      [&](const auto entity, const comp::DepthDrawable& drawable) noexcept {
        renderer.render_t(*drawable.texture, drawable.src, drawable.dst);

        if (const auto* hitbox = registry.try_get<comp::Hitbox>(entity);
            hitbox) {
          renderer.set_color(cen::colors::red);
          renderer.draw_rect_t(hitbox->bounds);
        }
      });
}

}  // namespace wanderer::sys