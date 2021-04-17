#include "chase_system.hpp"

#include "components/chase.hpp"
#include "components/humanoid_state.hpp"
#include "components/movable.hpp"
#include "systems/humanoid/humanoid_animation_system.hpp"
#include "systems/movement/direction_system.hpp"

namespace wanderer::sys {

void update_chase(entt::registry& registry, entt::dispatcher& dispatcher)
{
  const auto view = registry.view<comp::chase, comp::movable>();
  for (auto&& [entity, chase, movable] : view.each())
  {
    const auto& targetMovable = registry.get<comp::movable>(chase.target);

    if (distance(movable.position, targetMovable.position) <= chase.range)
    {
      movable.velocity = movable.position;
      movable.velocity.point_at(targetMovable.position, movable.speed);

      if (!registry.all_of<comp::humanoid_move>(entity))
      {
        registry.emplace<comp::humanoid_move>(entity);
        enter_move_animation(registry, entity, dominant_direction(movable));
      }
    }
    else
    {
      movable.velocity.zero();
      if (!registry.all_of<comp::humanoid_idle>(entity))
      {
        registry.emplace<comp::humanoid_idle>(entity);
        enter_idle_animation(registry, entity);
      }

      // TODO roam
    }
  }
}

}  // namespace wanderer::sys
