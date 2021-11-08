#include "chase_system.hpp"

#include "components/chase.hpp"
#include "components/humanoid.hpp"
#include "components/movable.hpp"
#include "components/roam.hpp"
#include "systems/ai/humanoid/humanoid_state_system.hpp"

namespace wanderer::sys {
namespace {

constexpr float cooldown_duration = 100;

void BeginChase(entt::registry& registry,
                const entt::entity entity,
                Chase& chase,
                Movable& movable,
                const Vec2 destination)
{
  registry.remove<Roam>(entity);

  movable.velocity = movable.position;
  LookAt(movable.velocity, destination, movable.speed);

  if (!registry.all_of<HumanoidMove>(entity)) {
    MakeHumanoidMove(registry, entity);
  }

  chase.active = true;
}

void EndChase(entt::registry& registry, const entt::entity entity, Chase& chase)
{
  if (chase.active) {
    if (!registry.all_of<HumanoidIdle>(entity)) {
      MakeHumanoidIdle(registry, entity);
    }

    if (!registry.all_of<Roam>(entity)) {
      auto& roam = registry.emplace<Roam>(entity);
      roam.cooldown_duration = cooldown_duration;
      roam.cooldown = 0;
    }
  }

  chase.active = false;
}

}  // namespace

void UpdateChase(entt::registry& registry)
{
  for (auto&& [entity, chase, movable] : registry.view<Chase, Movable>().each()) {
    const auto& targetMovable = registry.get<Movable>(chase.target);

    if (distance(movable.position, targetMovable.position) <= chase.range) {
      BeginChase(registry, entity, chase, movable, targetMovable.position);
    }
    else {
      EndChase(registry, entity, chase);
    }
  }
}

}  // namespace wanderer::sys
