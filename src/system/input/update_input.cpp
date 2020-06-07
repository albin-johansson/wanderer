#include "update_input.h"

#include "handle_idle_input.h"
#include "handle_move_input.h"

namespace wanderer {

void update_input(entt::registry& registry,
                  const entt::entity player,
                  const Input& input)
{
  handle_idle_input(registry, player, input);
  handle_move_input(registry, player, input);
}

}  // namespace wanderer
