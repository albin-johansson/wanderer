#include "player_input.h"

#include "player_idle_input.h"
#include "player_moving_input.h"

namespace wanderer {

void update_input(Registry& registry, const Input& input)
{
  handle_idle_input(registry, input);
  handle_move_input(registry, input);
}

}  // namespace wanderer
