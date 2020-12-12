#include "depth_drawables_system.hpp"

#include "animated_tile.hpp"
#include "depth_drawable.hpp"
#include "movable.hpp"
#include "tile_object.hpp"
#include "tile_rendering_system.hpp"

#ifndef NDEBUG
#include "centurion_utils.hpp"
#include "hitbox.hpp"
#endif

namespace wanderer::sys::depthdrawable {

void update_movable(entt::registry& registry)
{
  registry.view<comp::movable, comp::depth_drawable>().each(
      [](const comp::movable& movable,
         comp::depth_drawable& drawable) noexcept {
        drawable.dst.set_x(movable.position.x);
        drawable.dst.set_y(movable.position.y);
        drawable.centerY = movable.position.y + (drawable.dst.height() / 2.0f);
      });
}

void sort(entt::registry& registry)
{
  registry.sort<comp::depth_drawable>(
      [](const comp::depth_drawable& lhs,
         const comp::depth_drawable& rhs) noexcept {
        /* If both drawables feature layer indices that aren't the same,
         * then sort according to layer index. Otherwise, use the ordinary
         * depth and center Y-coordinate based sorting.
         */
        if (lhs.layer && rhs.layer && lhs.layer != rhs.layer) {
          return lhs.layer < rhs.layer;
        } else {
          return lhs.depth < rhs.depth ||
                 (rhs.depth >= lhs.depth && lhs.centerY < rhs.centerY);
        }
      },
      entt::insertion_sort{});
}

void update_tile_animations(entt::registry& registry,
                            const comp::tilemap::entity map)
{
  const auto& tilemap = registry.get<comp::tilemap>(map);
  const auto& tileset = registry.get<comp::tileset>(tilemap.tileset);

  registry.view<const comp::tile_object, comp::depth_drawable>().each(
      [&](const comp::tile_object& object, comp::depth_drawable& drawable) {
        if (registry.has<comp::animated_tile>(object.tileEntity)) {
          const auto& animated =
              tile::animated_tile(registry, object.tileEntity, tileset);
          drawable.src = animated.src;
        }
      });
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

#ifndef NDEBUG
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
#endif
      });
}

}  // namespace wanderer::sys::depthdrawable