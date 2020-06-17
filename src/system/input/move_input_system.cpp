#include "move_input_system.h"

#include "begin_attack_event.h"
#include "binds.h"
#include "direction.h"
#include "end_humanoid_move_event.h"
#include "movable.h"
#include "player.h"

namespace wanderer::system::input {
namespace {

void move(Movable& movable, const Direction direction) noexcept
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

void stop(Movable& movable, const Direction direction) noexcept
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

[[nodiscard]] bool check_pressed(Movable& movable,
                                 const Input& input,
                                 const Binds& binds)
{
  const auto left = input.is_pressed(binds.left);
  const auto right = input.is_pressed(binds.right);
  const auto up = input.is_pressed(binds.up);
  const auto down = input.is_pressed(binds.down);

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

void check_released(Movable& movable, const Input& input, const Binds& binds)
{
  const auto left = input.was_released(binds.left);
  const auto right = input.was_released(binds.right);
  const auto up = input.was_released(binds.up);
  const auto down = input.was_released(binds.down);

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

void handle_move_input(entt::registry& registry,
                       entt::dispatcher& dispatcher,
                       const entt::entity player,
                       const Input& input)
{
  if (registry.has<HumanoidMove>(player)) {
    const auto* binds = registry.try_get<Binds>(player);
    auto* movable = registry.try_get<Movable>(player);
    if (movable && binds) {
      const bool areMoveKeysDown = check_pressed(*movable, input, *binds);
      check_released(*movable, input, *binds);

      if (!areMoveKeysDown && movable->velocity.is_zero()) {
        dispatcher.enqueue<EndHumanoidMoveEvent>(&registry, player);
      } else if (input.is_pressed(binds->attack)) {
        movable->velocity.zero();

        // FIXME null weapon
        dispatcher.enqueue<BeginAttackEvent>(
            &registry, player, entt::null, movable->dominantDirection);
      }
    }
  }
}

}  // namespace wanderer::system::input
