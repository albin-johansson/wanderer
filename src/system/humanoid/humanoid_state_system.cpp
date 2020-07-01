#include "humanoid_state_system.h"

#include "end_attack_event.h"
#include "humanoid_state.h"

using wanderer::comp::HumanoidAttack;

namespace wanderer::sys::humanoid {
namespace {

void update_attacking_humanoids(entt::registry& registry,
                                entt::dispatcher& dispatcher)
{
  registry.view<HumanoidAttack>().each(
      [&](const auto entity, const HumanoidAttack& attack) {
        if (attack.done) {
          dispatcher.enqueue<EndAttackEvent>(
              &registry, entity, attack.weapon, Direction::Down);
        }
      });
}

}  // namespace

void update_state(entt::registry& registry, entt::dispatcher& dispatcher)
{
  update_attacking_humanoids(registry, dispatcher);
}

}  // namespace wanderer::sys::humanoid
