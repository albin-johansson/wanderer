#include "roam_system.hpp"

#include <rune.hpp>  // next_random

#include "components/humanoid_state.hpp"
#include "components/movable.hpp"
#include "components/roam.hpp"
#include "core/game_constants.hpp"
#include "systems/humanoid/humanoid_animation_system.hpp"
#include "systems/movement/direction_system.hpp"

namespace wanderer::sys {
namespace {

inline constexpr float cooldown_rate = 50;
inline constexpr float target_error_margin = 1;

[[nodiscard]] auto nearby_position(const float2 position) -> float2
{
  constexpr auto range = glob::tile_width<float> * 5.0f;

  const auto x = position.x + rune::next_random(-range, range);
  const auto y = position.y + rune::next_random(-range, range);

  return float2{x, y};
}

void target_nearby_position(entt::registry& registry,
                            const entt::entity entity,
                            comp::roam& roam,
                            comp::movable& movable)
{
  roam.cooldown = 0;
  roam.destination = nearby_position(movable.position);

  movable.velocity = movable.position;
  movable.velocity.look_at(*roam.destination, movable.speed);

  if (registry.all_of<comp::humanoid>(entity))
  {
    registry.emplace<comp::humanoid_move>(entity);
    enter_move_animation(registry, entity, dominant_direction(movable));
  }
}

void begin_cooldown(entt::registry& registry,
                    const entt::entity entity,
                    comp::roam& roam,
                    comp::movable& movable)
{
  // Reached destination, begin cooldown
  roam.cooldown = 0;
  roam.destination.reset();
  movable.velocity.reset();

  if (registry.all_of<comp::humanoid>(entity))
  {
    registry.emplace<comp::humanoid_idle>(entity);
    enter_idle_animation(registry, entity);
  }
}

}  // namespace

void update_roaming(entt::registry& registry, const rune::delta_time dt)
{
  for (auto&& [entity, roam, movable] : registry.view<comp::roam, comp::movable>().each())
  {
    if (!roam.destination)
    {
      roam.cooldown += cooldown_rate * dt;
      if (roam.cooldown >= roam.cooldown_duration)
      {
        target_nearby_position(registry, entity, roam, movable);
      }
    }
    else if (distance(movable.position, *roam.destination) < target_error_margin)
    {
      begin_cooldown(registry, entity, roam, movable);
    }
  }
}

}  // namespace wanderer::sys
