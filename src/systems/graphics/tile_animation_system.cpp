#include "tile_animation_system.hpp"

#include <centurion.hpp>  // ticks

#include "components/graphics/animated_tile.hpp"

namespace wanderer::sys {

void update_tile_animations(entt::registry& registry)
{
  for (auto&& [entity, tile] : registry.view<comp::animated_tile>().each())
  {
    const auto now = cen::counter::ticks();
    const auto elapsed = now - tile.then;
    if (elapsed >= tile.frames.at(tile.index).duration)
    {
      tile.then = now;
      ++tile.index;
      if (tile.index >= tile.frames.size())
      {
        tile.index = 0;
      }
    }
  }
}

}  // namespace wanderer::sys
