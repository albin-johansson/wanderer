#include "humanoid_state_system.h"

#include "end_attack_event.h"
#include "humanoid_state.h"

namespace wanderer::system::humanoid {

void update_state(entt::registry& registry, entt::dispatcher& dispatcher)
{
  registry.view<HumanoidAttack>().each(
      [&](const auto entity, const HumanoidAttack& attack) {
        if (attack.done) {
          EndAttackEvent event;
          event.registry = &registry;
          event.sourceEntity = entity;
          event.weapon = attack.weapon;
          dispatcher.enqueue<EndAttackEvent>(event);
        }
      });
}

}  // namespace wanderer::system::humanoid
