#include "animation_system.hpp"

#include "wanderer/core/centurion_utils.hpp"
#include "wanderer/data/components/rendering.hpp"
#include "wanderer/data/components/tags.hpp"
#include "wanderer/data/direction.hpp"
#include "wanderer/misc/assert.hpp"

namespace wanderer::sys {
namespace {

[[nodiscard]] auto _dominant_direction(const uint32 mask) -> uint32
{
  if (mask & direction_left_bit) {
    return direction_left_bit;
  }
  else if (mask & direction_right_bit) {
    return direction_right_bit;
  }
  else if (mask & direction_up_bit) {
    return direction_up_bit;
  }
  else if (mask & direction_down_bit) {
    return direction_down_bit;
  }
  else {
    return direction_down_bit;
  }
}

}  // namespace

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

void enter_humanoid_idle_animation(entt::registry& registry,
                                   const entt::entity humanoidEntity,
                                   const uint32 directionMask)
{
  WANDERER_ASSERT(humanoidEntity != entt::null);
  WANDERER_ASSERT(registry.all_of<comp::humanoid>(humanoidEntity));

  auto& animation = registry.get<comp::animation>(humanoidEntity);
  animation.then = cen::ticks64();
  animation.frame = 0;
  animation.frame_count = 1;

  using namespace cen::literals::time_literals;
  animation.delays.clear();
  animation.delays.push_back(100_ms);

  auto& drawable = registry.get<comp::drawable>(humanoidEntity);
  drawable.src.set_x(0);
  drawable.src.set_y(64);  // TODO direction
}

void enter_humanoid_walk_animation(entt::registry& registry,
                                   const entt::entity humanoidEntity,
                                   const uint32 directionMask)
{
  WANDERER_ASSERT(humanoidEntity != entt::null);
  WANDERER_ASSERT(registry.all_of<comp::humanoid>(humanoidEntity));

  auto& animation = registry.get<comp::animation>(humanoidEntity);
  animation.then = cen::ticks64();
  animation.frame = 0;
  animation.frame_count = 9;

  using namespace cen::literals::time_literals;
  animation.delays.clear();
  animation.delays.push_back(80_ms);

  const auto& seq = registry.get<comp::seq_animation>(humanoidEntity);
  auto& drawable = registry.get<comp::drawable>(humanoidEntity);
  drawable.src.set_x(0);

  const auto direction = _dominant_direction(directionMask);
  if (direction & direction_up_bit) {
    drawable.src.set_y(8 * seq.frame_size.y);
  }
  else if (direction & direction_left_bit) {
    drawable.src.set_y(9 * seq.frame_size.y);
  }
  else if (direction & direction_down_bit) {
    drawable.src.set_y(10 * seq.frame_size.y);
  }
  else if (direction & direction_right_bit) {
    drawable.src.set_y(11 * seq.frame_size.y);
  }
}

}  // namespace wanderer::sys