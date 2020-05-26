#include "player_idle_input.h"

#include "direction.h"
#include "player.h"

namespace wanderer {

void handle_idle_input(entt::registry& registry, const Input& input)
{
  const auto view = registry.view<Player, EntityIdleState>();
  for (const auto entity : view) {
    // TODO CTN 4.1 make Keys lazily initialized for their scancode/keycodes
    const auto left = input.is_pressed(SDL_SCANCODE_A);
    const auto right = input.is_pressed(SDL_SCANCODE_D);
    const auto up = input.is_pressed(SDL_SCANCODE_W);
    const auto down = input.is_pressed(SDL_SCANCODE_S);

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
    }
//    else if (input.is_pressed(SDL_SCANCODE_SPACE)) {
//      // TODO attack...
//    } else if (input.is_pressed(SDL_SCANCODE_U)) {
//      // TODO
//    }
  }
}

}  // namespace wanderer
