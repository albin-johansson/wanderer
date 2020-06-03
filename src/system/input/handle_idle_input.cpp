#include "handle_idle_input.h"

#include "binds.h"
#include "direction.h"
#include "humanoid_animation_system.h"
#include "player.h"

namespace wanderer {

void handle_idle_input(entt::registry& registry, const Input& input)
{
  const auto view = registry.view<Player, Binds, EntityIdleState>();
  for (const auto entity : view) {
    const auto& binds = view.get<Binds>(entity);

    const auto left = input.is_pressed(binds.left);
    const auto right = input.is_pressed(binds.right);
    const auto up = input.is_pressed(binds.up);
    const auto down = input.is_pressed(binds.down);

    if (left || right || up || down) {
      Direction direction;
      if (left) {
        direction = Direction::Left;
      } else if (right) {
        direction = Direction::Right;
      } else if (up) {
        direction = Direction::Up;
      } else if (down) {
        direction = Direction::Down;
      }
      registry.remove_if_exists<EntityIdleState>(entity);
      registry.emplace_or_replace<EntityMoveState>(entity, direction);
      enter_move(registry, entity, direction);
    }
    //    else if (input.is_pressed(SDL_SCANCODE_SPACE)) {
    //      // TODO attack...
    //    } else if (input.is_pressed(SDL_SCANCODE_U)) {
    //      // TODO
    //    }
  }
}

}  // namespace wanderer
