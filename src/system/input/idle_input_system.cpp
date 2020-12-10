#include "idle_input_system.hpp"

#include "component/begin_attack_event.hpp"
#include "component/begin_humanoid_move_event.hpp"
#include "component/binds.hpp"
#include "component/humanoid_state.hpp"
#include "component/player.hpp"
#include "direction.hpp"

namespace wanderer::sys::input {

void handle_idle_input(entt::registry& registry,
                       entt::dispatcher& dispatcher,
                       const comp::player::entity player,
                       const cen::key_state& keyState)
{
  if (registry.has<comp::humanoid_idle>(player.get())) {
    const auto& binds = registry.get<comp::binds>(player.get());

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
                                                          player.get(),
                                                          dir);
    } else if (keyState.is_pressed(binds.attack)) {
      // FIXME
      dispatcher.enqueue<comp::begin_attack_event>(&registry,
                                                   player.get(),
                                                   entt::null,
                                                   direction::down);
    }
  }
}

}  // namespace wanderer::sys::input
