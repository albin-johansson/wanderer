#include "input_system.hpp"

#include "humanoid_state.hpp"
#include "idle_input_system.hpp"
#include "move_input_system.hpp"

namespace wanderer::sys {

void update_input(entt::registry& registry,
                  entt::dispatcher& dispatcher,
                  const comp::player::entity player,
                  const cen::key_state& keyState)
{
  if (registry.has<comp::humanoid_idle>(player))
  {
    handle_idle_input(registry, dispatcher, player, keyState);

  } else if (registry.has<comp::humanoid_move>(player))
  {
    handle_move_input(registry, dispatcher, player, keyState);
  }
}

}  // namespace wanderer::sys
