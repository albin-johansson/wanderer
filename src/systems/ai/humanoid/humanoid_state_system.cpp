#include "humanoid_state_system.hpp"

#include <cassert>  // assert

#include "components/ai/humanoid.hpp"
#include "components/physics/movable.hpp"
#include "events/humanoid_events.hpp"
#include "humanoid_animation_system.hpp"
#include "systems/physics/direction_system.hpp"

namespace wanderer::sys {
namespace {

void UpdateAttackingHumanoids(entt::registry& registry, entt::dispatcher& dispatcher)
{
  for (auto&& [entity, attack] : registry.view<comp::HumanoidAttack>().each()) {
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
  assert(registry.all_of<comp::Humanoid>(entity));
  assert(!registry.all_of<comp::HumanoidIdle>(entity));

  auto& movable = registry.get<comp::Movable>(entity);
  movable.velocity.reset();

  registry.emplace<comp::HumanoidIdle>(entity);
  EnterIdleAnimation(registry, entity);
}

void MakeHumanoidMove(entt::registry& registry, entt::entity entity)
{
  assert(registry.all_of<comp::Humanoid>(entity));
  assert(!registry.all_of<comp::HumanoidMove>(entity));

  auto& movable = registry.get<comp::Movable>(entity);

  registry.emplace<comp::HumanoidMove>(entity);
  EnterMoveAnimation(registry, entity, GetDominantDirection(movable));
}

void UpdateHumanoidStates(entt::registry& registry, entt::dispatcher& dispatcher)
{
  UpdateAttackingHumanoids(registry, dispatcher);
}

}  // namespace wanderer::sys
