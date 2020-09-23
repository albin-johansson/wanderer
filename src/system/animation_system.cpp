#include "animation_system.hpp"

#include <counter.hpp>

#include "component/animated.hpp"

namespace wanderer::sys {

void update_animation_state(entt::registry& registry) noexcept
{
  registry.view<comp::animated>().each([](comp::animated& animated) noexcept {
    const auto now = cen::counter::ticks().count();  // FIXME
    const auto elapsed = now - animated.then;
    if (elapsed >= animated.delay) {
      animated.then = now;
      ++animated.frame;
      if (animated.frame >= animated.nFrames) {
        animated.frame = 0;
      }
    }
  });
}

}  // namespace wanderer::sys
