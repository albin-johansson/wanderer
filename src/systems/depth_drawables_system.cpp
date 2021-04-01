#include "depth_drawables_system.hpp"

#include <tuple>  // tie

#include "animated_tile.hpp"
#include "centurion_utils.hpp"
#include "depth_drawable.hpp"
#include "movable.hpp"
#include "render_bounds_system.hpp"
#include "tile_object.hpp"
#include "tile_rendering_system.hpp"

namespace wanderer::sys {

void update_drawable_movables(entt::registry& registry)
{
  const auto view = registry.view<const comp::movable, comp::depth_drawable>();
  view.each([](const comp::movable& movable, comp::depth_drawable& drawable) noexcept {
    drawable.dst.set_x(movable.position.x);
    drawable.dst.set_y(movable.position.y);
  });
}

void sort_drawables(entt::registry& registry)
{
  registry.sort<comp::depth_drawable>(
      [](const comp::depth_drawable& lhs, const comp::depth_drawable& rhs) noexcept {
        const auto lhsCenterY = lhs.dst.center_y();
        const auto rhsCenterY = rhs.dst.center_y();

        return std::tie(lhs.layer, lhs.depth, lhsCenterY) <
               std::tie(rhs.layer, rhs.depth, rhsCenterY);
      },
      entt::insertion_sort{});
}

void update_tile_object_animations(entt::registry& registry)
{
  const auto& tileset = registry.ctx<comp::tileset>();
  const auto view = registry.view<const comp::tile_object, comp::depth_drawable>();

  view.each([&](const comp::tile_object& object, comp::depth_drawable& drawable) {
    if (registry.has<comp::animated_tile>(object.tileEntity))
    {
      const auto& tile = get_animated_tile(registry, object.tileEntity, tileset);
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
  view.each([&](const comp::depth_drawable& drawable) noexcept {
    if (cen::intersects(boundsRect, drawable.dst))
    {
      const auto& texture = graphics.find(drawable.texture);
      renderer.render_t(texture, drawable.src, drawable.dst);
    }
  });
}

}  // namespace wanderer::sys