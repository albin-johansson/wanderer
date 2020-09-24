#include "input_system.hpp"

#include "idle_input_system.hpp"
#include "move_input_system.hpp"

namespace wanderer::sys::input {

void update(entt::registry& registry,
            entt::dispatcher& dispatcher,
            const entt::entity player,
            const cen::key_state& keyState)
{
  handle_idle_input(registry, dispatcher, player, keyState);
  handle_move_input(registry, dispatcher, player, keyState);
}

}  // namespace wanderer::sys::input
