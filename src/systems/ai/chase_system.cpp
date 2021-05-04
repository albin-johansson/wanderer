#include "chase_system.hpp"

#include "components/chase.hpp"
#include "components/humanoid_state.hpp"
#include "components/movable.hpp"
#include "components/roam.hpp"
#include "systems/humanoid/humanoid_state_system.hpp"

namespace wanderer::sys {
namespace {

inline constexpr float cooldown_duration = 100;

void begin_chase(entt::registry& registry,
                 const entt::entity entity,
                 comp::chase& chase,
                 comp::movable& movable,
                 const float2 destination)
{
  registry.remove_if_exists<comp::roam>(entity);

  movable.velocity = movable.position;
  movable.velocity.point_at(destination, movable.speed);

  if (!registry.all_of<comp::humanoid_move>(entity))
  {
    make_humanoid_move(registry, entity);
  }

  chase.active = true;
}

void end_chase(entt::registry& registry,
               const entt::entity entity,
               comp::chase& chase,
               comp::movable& movable)
{
  if (chase.active)
  {
    if (!registry.all_of<comp::humanoid_idle>(entity))
    {
      make_humanoid_idle(registry, entity);
    }

    if (!registry.all_of<comp::roam>(entity))
    {
      auto& roam = registry.emplace<comp::roam>(entity);
      roam.cooldownDuration = cooldown_duration;
      roam.cooldown = 0;
    }
  }

  chase.active = false;
}

}  // namespace

void update_chase(entt::registry& registry, entt::dispatcher& dispatcher)
{
  for (auto&& [entity, chase, movable] :
       registry.view<comp::chase, comp::movable>().each())
  {
    const auto& targetMovable = registry.get<comp::movable>(chase.target);

    if (distance(movable.position, targetMovable.position) <= chase.range)
    {
      begin_chase(registry, entity, chase, movable, targetMovable.position);
    }
    else
    {
      end_chase(registry, entity, chase, movable);
    }
  }
}

}  // namespace wanderer::sys
