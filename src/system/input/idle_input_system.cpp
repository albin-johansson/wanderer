#include "idle_input_system.h"

#include "begin_attack_event.h"
#include "begin_humanoid_move_event.h"
#include "binds.h"
#include "direction.h"
#include "player.h"

using wanderer::comp::Binds;
using wanderer::comp::HumanoidIdle;

namespace wanderer::system::input {

void handle_idle_input(entt::registry& registry,
                       entt::dispatcher& dispatcher,
                       const entt::entity player,
                       const Input& input)
{
  if (registry.has<HumanoidIdle>(player)) {
    // TODO make precondition
    if (const auto* binds = registry.try_get<Binds>(player); binds) {
      const auto left = input.is_pressed(binds->left);
      const auto right = input.is_pressed(binds->right);
      const auto up = input.is_pressed(binds->up);
      const auto down = input.is_pressed(binds->down);

      if (left || right || up || down) {
        Direction direction;
        if (left) {
          direction = Direction::Left;
        } else if (right) {
          direction = Direction::Right;
        } else if (up) {
          direction = Direction::Up;
        } else {
          direction = Direction::Down;
        }

        dispatcher.enqueue<BeginHumanoidMoveEvent>(
            &registry, player, direction);

      } else if (input.is_pressed(binds->attack)) {
        dispatcher.enqueue<BeginAttackEvent>(
            &registry, player, entt::null, Direction::Down);  // FIXME
      }
    }
  }
}

}  // namespace wanderer::system::input
