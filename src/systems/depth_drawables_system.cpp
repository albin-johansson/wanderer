#include "depth_drawables_system.hpp"

#include <tuple>  // tie

#include "animated_tile.hpp"
#include "centurion_utils.hpp"
#include "depth_drawable.hpp"
#include "hitbox.hpp"
#include "movable.hpp"
#include "render_bounds_system.hpp"
#include "tile_object.hpp"
#include "tile_rendering_system.hpp"

namespace wanderer::sys {
namespace {

void render_hitbox(cen::renderer& renderer, const comp::hitbox& hitbox) noexcept
{
  for (const auto& [offset, size] : hitbox.boxes) {
    const cen::frect rect{to_point(hitbox.origin + offset), size};

    renderer.set_color(cen::colors::magenta.with_alpha(100));
    renderer.draw_rect_t(rect);
  }

  renderer.set_color(cen::colors::red);
  renderer.draw_rect_t(hitbox.bounds);
}

}  // namespace

void update_drawable_movables(entt::registry& registry)
{
  const auto view = registry.view<comp::movable, comp::depth_drawable>();
  view.each([](const comp::movable& movable,
               comp::depth_drawable& drawable) noexcept {
    drawable.dst.set_x(movable.position.x);
    drawable.dst.set_y(movable.position.y);
    drawable.centerY = movable.position.y + (drawable.dst.height() / 2.0f);
  });
}

void sort_drawables(entt::registry& registry)
{
  registry.sort<comp::depth_drawable>(
      [](const comp::depth_drawable& lhs,
         const comp::depth_drawable& rhs) noexcept {
        return std::tie(lhs.layer, lhs.depth, lhs.centerY) <
               std::tie(rhs.layer, rhs.depth, rhs.centerY);
      },
      entt::insertion_sort{});
}

void update_tile_object_animations(entt::registry& registry,
                                   const comp::tileset::entity tilesetEntity)
{
  const auto& tileset = registry.get<comp::tileset>(tilesetEntity);
  const auto view =
      registry.view<const comp::tile_object, comp::depth_drawable>();

  view.each(
      [&](const comp::tile_object& object, comp::depth_drawable& drawable) {
        if (registry.has<comp::animated_tile>(object.tileEntity)) {
          const auto& tile =
              get_animated_tile(registry, object.tileEntity, tileset);
          drawable.src = tile.src;
        }
      });
}

void render_drawables(const entt::registry& registry,
                      graphics_context& graphics,
                      const comp::render_bounds& bounds)
{
  auto& renderer = graphics.renderer();
  const auto boundsRect = to_rect(bounds);

  const auto view = registry.view<const comp::depth_drawable>();
  view.each([&](auto entity, const comp::depth_drawable& drawable) noexcept {
    if (cen::intersects(boundsRect, drawable.dst)) {
      const auto& texture = graphics.find(drawable.texture);
      renderer.render_t(texture, drawable.src, drawable.dst);

      if constexpr (cen::is_debug_build()) {
        if (const auto* hitbox = registry.try_get<comp::hitbox>(entity)) {
          render_hitbox(renderer, *hitbox);
        }
      }
    }
  });
}

}  // namespace wanderer::sys