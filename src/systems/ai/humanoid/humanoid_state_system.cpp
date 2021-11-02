#include "humanoid_state_system.hpp"

#include <cassert>  // assert

#include "components/humanoid.hpp"
#include "components/movable.hpp"
#include "events/humanoid_events.hpp"
#include "humanoid_animation_system.hpp"
#include "systems/physics/direction_system.hpp"

namespace wanderer::sys {
namespace {

void UpdateAttackingHumanoids(entt::registry& registry, entt::dispatcher& dispatcher)
{
  for (auto&& [entity, attack] : registry.view<HumanoidAttack>().each()) {
    if (attack.done) {
      dispatcher.enqueue<EndAttackEvent>(registry,
                                         dispatcher,
                                         entity,
                                         attack.weapon,
                                         Direction::Down);
    }
  }
}

}  // namespace

void MakeHumanoidIdle(entt::registry& registry, entt::entity entity)
{
  assert(registry.all_of<Humanoid>(entity));
  assert(!registry.all_of<HumanoidIdle>(entity));

  auto& movable = registry.get<Movable>(entity);
  movable.velocity.x = 0;
  movable.velocity.y = 0;

  registry.emplace<HumanoidIdle>(entity);
  EnterIdleAnimation(registry, entity);
}

void MakeHumanoidMove(entt::registry& registry, entt::entity entity)
{
  assert(registry.all_of<Humanoid>(entity));
  assert(!registry.all_of<HumanoidMove>(entity));

  auto& movable = registry.get<Movable>(entity);

  registry.emplace<HumanoidMove>(entity);
  EnterMoveAnimation(registry, entity, GetDominantDirection(movable));
}

void UpdateHumanoidStates(entt::registry& registry, entt::dispatcher& dispatcher)
{
  UpdateAttackingHumanoids(registry, dispatcher);
}

}  // namespace wanderer::sys
