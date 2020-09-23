#include "render_depth_drawables_system.hpp"

#include "depth_drawable.hpp"
#include "hitbox.hpp"

namespace wanderer::sys {

void render_depth_drawables(entt::registry& registry, cen::renderer& renderer)
{
  // TODO could have movables signal events when they have moved to check if
  //  they are within the viewport bounds and therefore should be rendered,
  //  this would make it possible to have a "InBounds" component

  registry.sort<comp::depth_drawable>(
      [](const comp::depth_drawable& lhs,
         const comp::depth_drawable& rhs) noexcept {
        return lhs.depth < rhs.depth ||
               (rhs.depth >= lhs.depth && lhs.centerY < rhs.centerY);
      },
      entt::insertion_sort{});

  registry.view<comp::depth_drawable>().each(
      [&](const auto entity, const comp::depth_drawable& drawable) noexcept {
        renderer.render_t(*drawable.texture, drawable.src, drawable.dst);

        if (const auto* hitbox = registry.try_get<comp::Hitbox>(entity);
            hitbox) {
          renderer.set_color(cen::colors::red);
          renderer.draw_rect_t(hitbox->bounds);
        }
      });
}

}  // namespace wanderer::sys