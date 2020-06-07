#include "handle_idle_input.h"

#include "binds.h"
#include "direction.h"
#include "humanoid_animation_system.h"
#include "player.h"

namespace wanderer {

void handle_idle_input(entt::registry& registry,
                       entt::entity player,
                       const Input& input)
{
  if (registry.has<Player>(player) && registry.has<HumanoidIdle>(player)) {
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
        registry.remove_if_exists<HumanoidIdle>(player);
        registry.emplace_or_replace<HumanoidMove>(player);
        humanoid_enter_move_animation(registry, player, direction);
      } else if (input.is_pressed(binds->attack)) {
        registry.remove_if_exists<HumanoidIdle>(player);
        registry.emplace_or_replace<HumanoidAttack>(player);
        humanoid_enter_melee_animation(registry,
                                       player);  // TODO check selected item
      }
    }
  }
}

}  // namespace wanderer
