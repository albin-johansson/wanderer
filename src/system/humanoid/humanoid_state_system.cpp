#include "humanoid_state_system.hpp"

#include "end_attack_event.hpp"
#include "humanoid_state.hpp"

namespace wanderer::sys {
namespace {

void update_attacking_humanoids(entt::registry& registry,
                                entt::dispatcher& dispatcher)
{
  registry.view<comp::humanoid_attack>().each(
      [&](const entt::entity entity, const comp::humanoid_attack& attack) {
        if (attack.done) {
          dispatcher.enqueue<comp::end_attack_event>(&registry,
                                                     entity,
                                                     attack.weapon,
                                                     direction::down);
        }
      });
}

}  // namespace

void update_humanoid_states(entt::registry& registry, entt::dispatcher&
                                                        dispatcher)
{
  update_attacking_humanoids(registry, dispatcher);
}

}  // namespace wanderer::sys
