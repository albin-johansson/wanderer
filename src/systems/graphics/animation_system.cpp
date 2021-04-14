#include "animation_system.hpp"

#include <centurion.hpp>  // ticks

#include "animated.hpp"

namespace wanderer::sys {

void update_animations(entt::registry& registry) noexcept
{
  const auto view = registry.view<comp::animated>();
  for (auto&& [entity, animated] : view.each())
  {
    const auto now = cen::counter::ticks();
    const auto elapsed = now - animated.then;
    if (elapsed >= animated.delay)
    {
      animated.then = now;
      ++animated.frame;
      if (animated.frame >= animated.nFrames)
      {
        animated.frame = 0;
      }
    }
  }
}

}  // namespace wanderer::sys
