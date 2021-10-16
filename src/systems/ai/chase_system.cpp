#include "chase_system.hpp"

#include "components/ai/chase.hpp"
#include "components/ai/humanoid.hpp"
#include "components/ai/roam.hpp"
#include "components/physics/movable.hpp"
#include "systems/ai/humanoid/humanoid_state_system.hpp"

namespace wanderer::sys {
namespace {

inline constexpr float cooldown_duration = 100;

void begin_chase(entt::registry& registry,
                 const entt::entity entity,
                 comp::Chase& chase,
                 comp::Movable& movable,
                 const float2 destination)
{
  registry.remove<comp::Roam>(entity);

  movable.velocity = movable.position;
  movable.velocity.look_at(destination, movable.speed);

  if (!registry.all_of<comp::HumanoidMove>(entity)) {
    make_humanoid_move(registry, entity);
  }

  chase.active = true;
}

void end_chase(entt::registry& registry, const entt::entity entity, comp::Chase& chase)
{
  if (chase.active) {
    if (!registry.all_of<comp::HumanoidIdle>(entity)) {
      make_humanoid_idle(registry, entity);
    }

    if (!registry.all_of<comp::Roam>(entity)) {
      auto& roam = registry.emplace<comp::Roam>(entity);
      roam.cooldown_duration = cooldown_duration;
      roam.cooldown = 0;
    }
  }

  chase.active = false;
}

}  // namespace

void update_chase(entt::registry& registry)
{
  for (auto&& [entity, chase, movable] :
       registry.view<comp::Chase, comp::Movable>().each()) {
    const auto& targetMovable = registry.get<comp::Movable>(chase.target);

    if (distance(movable.position, targetMovable.position) <= chase.range) {
      begin_chase(registry, entity, chase, movable, targetMovable.position);
    }
    else {
      end_chase(registry, entity, chase);
    }
  }
}

}  // namespace wanderer::sys
