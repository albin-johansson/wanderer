#include "depth_drawables_system.hpp"

#include <cen/log.hpp>

#include "centurion_utils.hpp"
#include "component/depth_drawable.hpp"
#include "component/hitbox.hpp"

namespace wanderer::sys::depthdrawable {

void sort(entt::registry& registry)
{
  registry.sort<comp::depth_drawable>(
      [](const comp::depth_drawable& lhs,
         const comp::depth_drawable& rhs) noexcept {
        return lhs.depth < rhs.depth ||
               (rhs.depth >= lhs.depth && lhs.centerY < rhs.centerY);
      },
      entt::insertion_sort{});
}

void render(const entt::registry& registry, cen::renderer& renderer)
{
  // TODO only render tile object depth_drawables in bounds

  // TODO could have movables signal events when they have moved to check if
  //  they are within the viewport bounds and therefore should be rendered,
  //  this would make it possible to have a "InBounds" component

  registry.view<const comp::depth_drawable>().each(
      [&](const entt::entity entity,
          const comp::depth_drawable& drawable) noexcept {
        renderer.render_t(*drawable.texture, drawable.src, drawable.dst);

        if (const auto* hitbox = registry.try_get<comp::hitbox>(entity)) {
          const auto origin = hitbox->origin;

          for (const auto& [offset, size] : hitbox->boxes) {
            const cen::frect rect{to_point(hitbox->origin + offset), size};

            renderer.set_color(cen::colors::magenta.with_alpha(100));
            renderer.draw_rect_t(rect);
          }

          renderer.set_color(cen::colors::red);
          renderer.draw_rect_t(hitbox->bounds);
        }
      });
}

}  // namespace wanderer::sys::depthdrawable