#include "animation_system.hpp"

#include <centurion.hpp>  // ticks

#include "components/gfx/animation.hpp"

namespace wanderer::sys {

void update_animations(entt::registry& registry)
{
  for (auto&& [entity, animation] : registry.view<comp::animation>().each()) {
    const auto now = cen::counter::ticks();
    const auto elapsed = now - animation.then;
    if (elapsed >= animation.delay) {
      animation.then = now;
      ++animation.frame;
      if (animation.frame >= animation.frame_count) {
        animation.frame = 0;
      }
    }
  }
}

}  // namespace wanderer::sys