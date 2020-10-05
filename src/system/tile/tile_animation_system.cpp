#include "tile_animation_system.hpp"

#include <cen/counter.hpp>

#include "component/animated_tile.hpp"

namespace wanderer::sys::tile {

void update_animation(entt::registry& registry)
{
  registry.view<comp::animated_tile>().each(
      [](comp::animated_tile& animatedTile) {
        const auto now = cen::counter::ticks();
        const auto elapsed = now - animatedTile.then;
        if (elapsed >= animatedTile.frames.at(animatedTile.index).duration) {
          animatedTile.then = now;
          ++animatedTile.index;
          if (animatedTile.index >= animatedTile.frames.size()) {
            animatedTile.index = 0;
          }
        }
      });
}

}  // namespace wanderer::sys::tile
