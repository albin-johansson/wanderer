#include "debug_rendering_system.hpp"

#include "centurion_utils.hpp"
#include "chase.hpp"
#include "depth_drawable.hpp"
#include "hitbox.hpp"

namespace wanderer::sys {
namespace {

void render_hitboxes(const entt::registry& registry, cen::renderer& renderer)
{
  const auto view = registry.view<const comp::hitbox>();
  view.each([&](const comp::hitbox& hitbox) {
    for (const auto& [offset, size] : hitbox.boxes)
    {
      const cen::frect rect{to_point(hitbox.origin + offset), size};

      renderer.set_color(cen::colors::magenta.with_alpha(100));
      renderer.draw_rect_t(rect);
    }

    renderer.set_color(cen::colors::red);
    renderer.draw_rect_t(hitbox.bounds);
  });
}

void render_chase_ranges(const entt::registry& registry,
                         cen::renderer& renderer)
{
  renderer.set_color(cen::colors::red);

  const auto view =
      registry.view<const comp::depth_drawable, const comp::chase>();
  view.each(
      [&](const comp::depth_drawable& drawable, const comp::chase& chase) {
        renderer.draw_circle_t(drawable.dst.center(), chase.range);
      });
}

}  // namespace

void render_debug_info(const entt::registry& registry,
                       graphics_context& graphics)
{
  auto& renderer = graphics.renderer();
  render_hitboxes(registry, renderer);
  render_chase_ranges(registry, renderer);
}

}  // namespace wanderer::sys
