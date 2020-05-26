#include "player_moving_input.h"

#include "direction.h"
#include "movable.h"
#include "player.h"

namespace wanderer {
namespace {

void move(Movable& movable, Direction direction) noexcept
{
  switch (direction) {
    case Direction::Right: {
      movable.velocity.x = movable.speed;
      break;
    }
    case Direction::Left: {
      movable.velocity.x = -movable.speed;
      break;
    }
    case Direction::Up: {
      movable.velocity.y = -movable.speed;
      break;
    }
    case Direction::Down: {
      movable.velocity.y = movable.speed;
      break;
    }
    default:
      break;
  }
  movable.velocity.norm();
  movable.velocity.scale(movable.speed);
}

void stop(Movable& movable, Direction direction) noexcept
{
  switch (direction) {
    case Direction::Right:
      [[fallthrough]];
    case Direction::Left: {
      movable.velocity.x = 0;
      break;
    }
    case Direction::Up:
      [[fallthrough]];
    case Direction::Down: {
      movable.velocity.y = 0;
      break;
    }
    default:
      break;
  }
  movable.velocity.norm();
  movable.velocity.scale(movable.speed);
}

bool check_pressed(Movable& movable, const Input& input)
{
  // FIXME this needs to be stored somewhere else
  const auto left = input.is_pressed(SDL_SCANCODE_A);
  const auto right = input.is_pressed(SDL_SCANCODE_D);
  const auto up = input.is_pressed(SDL_SCANCODE_W);
  const auto down = input.is_pressed(SDL_SCANCODE_S);

  if (left && right) {
    stop(movable, Direction::Left);
    stop(movable, Direction::Right);
  } else if (left) {
    move(movable, Direction::Left);
  } else if (right) {
    move(movable, Direction::Right);
  }

  if (up && down) {
    stop(movable, Direction::Up);
    stop(movable, Direction::Down);
  } else if (up) {
    move(movable, Direction::Up);
  } else if (down) {
    move(movable, Direction::Down);
  }

  return up || down || right || left;
}

void check_released(Movable& movable, const Input& input)
{
  const auto left = input.was_released(SDL_SCANCODE_A);
  const auto right = input.was_released(SDL_SCANCODE_D);
  const auto up = input.was_released(SDL_SCANCODE_W);
  const auto down = input.was_released(SDL_SCANCODE_S);

  if (left) {
    stop(movable, Direction::Left);
  }

  if (right) {
    stop(movable, Direction::Right);
  }

  if (up) {
    stop(movable, Direction::Up);
  }

  if (down) {
    stop(movable, Direction::Down);
  }
}

}  // namespace

void handle_move_input(entt::registry& registry, const Input& input)
{
  const auto view = registry.view<Player, Movable, EntityMoveState>();
  for (const auto entity : view) {
    auto& movable = view.get<Movable>(entity);

    bool areMoveKeysDown = false;  // assume no movement keys are down

    areMoveKeysDown = check_pressed(movable, input);
    check_released(movable, input);

    if (!areMoveKeysDown && movable.velocity.is_zero()) {
      registry.remove_if_exists<EntityMoveState>(entity);
      registry.emplace_or_replace<EntityIdleState>(entity);
    }
//    else if (input.is_pressed(SDL_SCANCODE_SPACE)) { // TODO
//      registry.remove_if_exists<EntityMoveState>(entity);
//      registry.emplace_or_replace<EntityAttackState>(entity);
//    }
  }
}

}  // namespace wanderer
