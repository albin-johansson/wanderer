#include "update_input.h"

#include "handle_idle_input.h"
#include "handle_move_input.h"

namespace wanderer {

void update_input(entt::registry& registry, const Input& input)
{
  handle_idle_input(registry, input);
  handle_move_input(registry, input);
}

}  // namespace wanderer
