#include "animation_system.hpp"

#include <cen/counter.hpp>

#include "component/animated.hpp"

namespace wanderer::sys::animated {

void update(entt::registry& registry) noexcept
{
  registry.view<comp::animated>().each([](comp::animated& animated) {
    const auto now = cen::counter::ticks();
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

}  // namespace wanderer::sys::animated
