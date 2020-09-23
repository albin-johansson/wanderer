#include "input_system.hpp"

#include "idle_input_system.hpp"
#include "move_input_system.hpp"

namespace wanderer::sys::input {

void update(entt::registry& registry,
            entt::dispatcher& dispatcher,
            const entt::entity player,
            const Input& input)
{
  handle_idle_input(registry, dispatcher, player, input);
  handle_move_input(registry, dispatcher, player, input);
}

}  // namespace wanderer::sys::input
