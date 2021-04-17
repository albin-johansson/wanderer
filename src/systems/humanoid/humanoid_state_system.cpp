#include "humanoid_state_system.hpp"

#include "components/humanoid_state.hpp"
#include "events/end_attack_event.hpp"

namespace wanderer::sys {
namespace {

void update_attacking_humanoids(entt::registry& registry, entt::dispatcher& dispatcher)
{
  for (auto&& [entity, attack] : registry.view<comp::humanoid_attack>().each())
  {
    if (attack.done)
    {
      dispatcher.enqueue<event::end_attack>(registry,
                                            dispatcher,
                                            entity,
                                            attack.weapon,
                                            direction::down);
    }
  }
}

}  // namespace

void update_humanoid_states(entt::registry& registry, entt::dispatcher& dispatcher)
{
  update_attacking_humanoids(registry, dispatcher);
}

}  // namespace wanderer::sys
