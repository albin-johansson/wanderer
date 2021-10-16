#include "tile_animation_system.hpp"

#include <centurion.hpp>  // ticks

#include "components/gfx/tile_animation.hpp"

namespace wanderer::sys {

void update_tile_animations(entt::registry& registry)
{
  for (auto&& [entity, animation] : registry.view<comp::TileAnimation>().each()) {
    const auto now = cen::counter::ticks();
    const auto elapsed = now - animation.then;
    if (elapsed >= animation.frames.at(animation.index).duration) {
      animation.then = now;
      ++animation.index;
      if (animation.index >= animation.frames.size()) {
        animation.index = 0;
      }
    }
  }
}

}  // namespace wanderer::sys
