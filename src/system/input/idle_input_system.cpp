#include "idle_input_system.hpp"

#include "begin_attack_event.hpp"
#include "begin_humanoid_move_event.hpp"
#include "binds.hpp"
#include "direction.hpp"
#include "humanoid_state.hpp"
#include "interact_event.hpp"
#include "player.hpp"

namespace wanderer::sys::input {

void handle_idle_input(entt::registry& registry,
                       entt::dispatcher& dispatcher,
                       const comp::player::entity player,
                       const cen::key_state& keyState)
{
  if (registry.has<comp::humanoid_idle>(player)) {
    const auto& binds = registry.get<comp::binds>(player);

    const auto left = keyState.is_pressed(binds.left);
    const auto right = keyState.is_pressed(binds.right);
    const auto up = keyState.is_pressed(binds.up);
    const auto down = keyState.is_pressed(binds.down);

    if (left || right || up || down) {
      direction dir;
      if (left) {
        dir = direction::left;
      } else if (right) {
        dir = direction::right;
      } else if (up) {
        dir = direction::up;
      } else {
        dir = direction::down;
      }

      dispatcher.enqueue<comp::begin_humanoid_move_event>(&registry,
                                                          player,
                                                          dir);
    } else if (keyState.is_pressed(binds.attack)) {
      // FIXME
      dispatcher.enqueue<comp::begin_attack_event>(&registry,
                                                   player,
                                                   entt::null,
                                                   direction::down);
    } else if (keyState.was_just_released(binds.interact)) {
      dispatcher.enqueue<comp::interact_event>(&registry, &dispatcher, player);
    }
  }
}

}  // namespace wanderer::sys::input
