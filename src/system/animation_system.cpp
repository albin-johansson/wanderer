#include "animation_system.h"

#include <timer.h>

#include "animated.h"

using ctn::Timer;

namespace wanderer::system {

void update_animation_state(entt::registry& registry) noexcept
{
  registry.view<Animated>().each([](Animated& animated) noexcept {
    const auto now = Timer::millis();
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

}  // namespace wanderer::system
