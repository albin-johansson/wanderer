#include "animation_system.hpp"

#include "wanderer/data/components/rendering.hpp"

namespace wanderer::sys {

void update_animations(entt::registry& registry)
{
  for (auto&& [entity, animation] : registry.view<comp::animation>().each()) {
    const auto now = cen::ticks64();
    const auto elapsed = now - animation.then;
    if (elapsed >= animation.delays.at(animation.frame)) {
      animation.then = now;
      animation.frame = (animation.frame + 1u) % animation.frame_count;
    }
  }
}

}  // namespace wanderer::sys