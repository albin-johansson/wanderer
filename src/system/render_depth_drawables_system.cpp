#include "render_depth_drawables_system.h"

#include "depth_drawable.h"
#include "hitbox.h"

using wanderer::comp::DepthDrawable;

namespace wanderer::sys {

void render_depth_drawables(entt::registry& registry, cen::renderer& renderer)
{
  // TODO could have movables signal events when they have moved to check if
  //  they are within the viewport bounds and therefore should be rendered,
  //  this would make it possible to have a "InBounds" component

  registry.sort<DepthDrawable>(
      [](const DepthDrawable& lhs, const DepthDrawable& rhs) noexcept {
        return lhs.depth < rhs.depth ||
               (rhs.depth >= lhs.depth && lhs.centerY < rhs.centerY);
      },
      entt::insertion_sort{});

  registry.view<DepthDrawable>().each(
      [&](const auto entity, const DepthDrawable& drawable) noexcept {
        renderer.render_t(*drawable.texture, drawable.src, drawable.dst);

        if (const auto* hitbox = registry.try_get<comp::Hitbox>(entity);
            hitbox) {
          renderer.set_color(cen::colors::red);
          renderer.draw_rect_t(hitbox->bounds);
        }
      });
}

}  // namespace wanderer::sys
