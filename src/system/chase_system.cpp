#include "chase_system.hpp"

#include "chase.hpp"
#include "humanoid_animation_system.hpp"
#include "humanoid_state.hpp"
#include "movable.hpp"
#include "movable_system.hpp"

namespace wanderer::sys {

void update_chase(entt::registry& registry, entt::dispatcher& dispatcher)
{
  const auto view = registry.view<comp::chase>();
  view.each([&](const entt::entity entity, comp::chase& chase) {
    const auto& targetMovable = registry.get<comp::movable>(chase.target);
    auto& movable = registry.get<comp::movable>(entity);

    if (distance(movable.position, targetMovable.position) <= chase.range) {
      movable.velocity = movable.position;
      movable.velocity.point_at(targetMovable.position, movable.speed);

      if (!registry.has<comp::humanoid_move>(entity)) {
        registry.emplace<comp::humanoid_move>(entity);
        enter_move_animation(registry, entity, dominant_direction(movable));
      }

    } else {
      movable.velocity.zero();
      if (!registry.has<comp::humanoid_idle>(entity)) {
        registry.emplace<comp::humanoid_idle>(entity);
        enter_idle_animation(registry, entity);
      }

      // TODO roam
    }
  });
}

}  // namespace wanderer::sys
