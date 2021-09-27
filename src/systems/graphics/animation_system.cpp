#include "animation_system.hpp"

#include <centurion.hpp>  // ticks

#include "components/gfx/animated.hpp"

namespace wanderer::sys {

void update_animations(entt::registry& registry)
{
  for (auto&& [entity, animated] : registry.view<comp::animated>().each()) {
    const auto now = cen::counter::ticks();
    const auto elapsed = now - animated.then;
    if (elapsed >= animated.delay) {
      animated.then = now;
      ++animated.frame;
      if (animated.frame >= animated.frame_count) {
        animated.frame = 0;
      }
    }
  }
}

}  // namespace wanderer::sys
