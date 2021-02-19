#include "tile_animation_system.hpp"

#include <cen/counter.hpp>

#include "animated_tile.hpp"

namespace wanderer::sys {

void update_tile_animations(entt::registry& registry)
{
  registry.view<comp::animated_tile>().each([](comp::animated_tile& tile) {
    const auto now = cen::counter::ticks();
    const auto elapsed = now - tile.then;
    if (elapsed >= tile.frames.at(tile.index).duration) {
      tile.then = now;
      ++tile.index;
      if (tile.index >= tile.frames.size()) {
        tile.index = 0;
      }
    }
  });
}

}  // namespace wanderer::sys
