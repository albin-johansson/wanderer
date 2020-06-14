#include "animation_system.h"

#include <timer.h>

#include "animated.h"

using namespace centurion;

namespace wanderer::system {

void update_animation_state(entt::registry& registry) noexcept
{
  const auto entities = registry.view<Animated>();
  for (const auto entity : entities) {
    auto& animated = entities.get<Animated>(entity);

    const auto now = Timer::millis();
    const auto elapsed = now - animated.then;
    if (elapsed >= animated.delay) {
      animated.then = now;
      ++animated.frame;
      if (animated.frame >= animated.nFrames) {
        animated.frame = 0;
      }
    }
  }
}

}  // namespace wanderer::system
