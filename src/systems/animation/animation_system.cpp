#include "animation_system.hpp"

#include <centurion.hpp>  // ticks

#include "components/gfx/animation.hpp"

namespace wanderer::sys {

void UpdateAnimations(entt::registry& registry)
{
  for (auto&& [entity, animation] : registry.view<comp::Animation>().each()) {
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
