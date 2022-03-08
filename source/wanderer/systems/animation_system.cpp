#include "animation_system.hpp"

#include "wanderer/data/components/rendering.hpp"

namespace wanderer::sys {

void update_animations(entt::registry& registry)
{
  for (auto&& [entity, animation] : registry.view<comp::animation>().each()) {
    const auto now = cen::ticks64();
    const auto elapsed = now - animation.then;

    const auto frameDuration = animation.delays.size() == 1
                                   ? animation.delays.front()
                                   : animation.delays.at(animation.frame);

    if (elapsed >= frameDuration) {
      animation.then = now;
      animation.frame = (animation.frame + 1u) % animation.frame_count;
    }
  }

  for (auto&& [entity, animation, seq, drawable] :
       registry.view<comp::animation, comp::seq_animation, comp::drawable>().each()) {
    drawable.src.set_x(static_cast<int32>(animation.frame) * seq.frame_size.x);
  }
}
}

}  // namespace wanderer::sys