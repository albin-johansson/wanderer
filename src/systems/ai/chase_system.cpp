#include "chase_system.hpp"

#include "components/ai/chase.hpp"
#include "components/ai/humanoid.hpp"
#include "components/ai/roam.hpp"
#include "components/physics/movable.hpp"
#include "systems/ai/humanoid/humanoid_state_system.hpp"

namespace wanderer::sys {
namespace {

inline constexpr float cooldown_duration = 100;

void BeginChase(entt::registry& registry,
                const entt::entity entity,
                comp::Chase& chase,
                comp::Movable& movable,
                const float2 destination)
{
  registry.remove<comp::Roam>(entity);

  movable.velocity = movable.position;
  movable.velocity.look_at(destination, movable.speed);

  if (!registry.all_of<comp::HumanoidMove>(entity)) {
    MakeHumanoidMove(registry, entity);
  }

  chase.active = true;
}

void EndChase(entt::registry& registry, const entt::entity entity, comp::Chase& chase)
{
  if (chase.active) {
    if (!registry.all_of<comp::HumanoidIdle>(entity)) {
      MakeHumanoidIdle(registry, entity);
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

void UpdateChase(entt::registry& registry)
{
  for (auto&& [entity, chase, movable] :
       registry.view<comp::Chase, comp::Movable>().each()) {
    const auto& targetMovable = registry.get<comp::Movable>(chase.target);

    if (distance(movable.position, targetMovable.position) <= chase.range) {
      BeginChase(registry, entity, chase, movable, targetMovable.position);
    }
    else {
      EndChase(registry, entity, chase);
    }
  }
}

}  // namespace wanderer::sys
