#include "input_system.h"

#include "idle_input_system.h"
#include "move_input_system.h"

namespace wanderer::system::input {

void update(entt::registry& registry,
            entt::dispatcher& dispatcher,
            const entt::entity player,
            const Input& input)
{
  handle_idle_input(registry, dispatcher, player, input);
  handle_move_input(registry, dispatcher, player, input);
}

}  // namespace wanderer::system::input
