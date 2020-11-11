#include "humanoid_state_system.hpp"

#include "component/end_attack_event.hpp"
#include "component/humanoid_state.hpp"

namespace wanderer::sys::humanoid {
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

void update_state(entt::registry& registry, entt::dispatcher& dispatcher)
{
  update_attacking_humanoids(registry, dispatcher);
}

}  // namespace wanderer::sys::humanoid
