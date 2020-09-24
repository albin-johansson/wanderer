#include "move_input_system.hpp"

#include "component/binds.hpp"
#include "component/event/begin_attack_event.hpp"
#include "component/event/end_humanoid_move_event.hpp"
#include "component/humanoid_state.hpp"
#include "component/movable.hpp"
#include "component/player.hpp"
#include "direction.hpp"

namespace wanderer::sys::input {
namespace {

void move(comp::movable& movable, const direction direction) noexcept
{
  switch (direction) {
    case direction::right: {
      movable.velocity.set_x(movable.speed);
      break;
    }
    case direction::left: {
      movable.velocity.set_x(-movable.speed);
      break;
    }
    case direction::up: {
      movable.velocity.set_y(-movable.speed);
      break;
    }
    case direction::down: {
      movable.velocity.set_y(movable.speed);
      break;
    }
    default:
      break;
  }
  movable.velocity.norm();
  movable.velocity.scale(movable.speed);
}

void stop(comp::movable& movable, const direction direction) noexcept
{
  switch (direction) {
    case direction::right:
      [[fallthrough]];
    case direction::left: {
      movable.velocity.set_x(0);
      break;
    }
    case direction::up:
      [[fallthrough]];
    case direction::down: {
      movable.velocity.set_y(0);
      break;
    }
    default:
      break;
  }
  movable.velocity.norm();
  movable.velocity.scale(movable.speed);
}

[[nodiscard]] auto check_pressed(comp::movable& movable,
                                 const Input& input,
                                 const comp::binds& binds) -> bool
{
  const auto left = input.is_pressed(binds.left);
  const auto right = input.is_pressed(binds.right);
  const auto up = input.is_pressed(binds.up);
  const auto down = input.is_pressed(binds.down);

  if (left && right) {
    stop(movable, direction::left);
    stop(movable, direction::right);
  } else if (left) {
    move(movable, direction::left);
  } else if (right) {
    move(movable, direction::right);
  }

  if (up && down) {
    stop(movable, direction::up);
    stop(movable, direction::down);
  } else if (up) {
    move(movable, direction::up);
  } else if (down) {
    move(movable, direction::down);
  }

  return up || down || right || left;
}

void check_released(comp::movable& movable,
                    const Input& input,
                    const comp::binds& binds)
{
  const auto left = input.was_released(binds.left);
  const auto right = input.was_released(binds.right);
  const auto up = input.was_released(binds.up);
  const auto down = input.was_released(binds.down);

  if (left) {
    stop(movable, direction::left);
  }

  if (right) {
    stop(movable, direction::right);
  }

  if (up) {
    stop(movable, direction::up);
  }

  if (down) {
    stop(movable, direction::down);
  }
}

}  // namespace

void handle_move_input(entt::registry& registry,
                       entt::dispatcher& dispatcher,
                       const entt::entity player,
                       const Input& input)
{
  if (registry.has<comp::humanoid_move>(player)) {
    auto& movable = registry.get<comp::movable>(player);
    const auto& binds = registry.get<comp::binds>(player);
    const bool areMoveKeysDown = check_pressed(movable, input, binds);
    check_released(movable, input, binds);

    if (!areMoveKeysDown && movable.velocity.is_zero()) {
      dispatcher.enqueue(end_humanoid_move_event{&registry, player});
    } else if (input.is_pressed(binds.attack)) {
      movable.velocity.zero();

      // FIXME null weapon
      dispatcher.enqueue(begin_attack_event{
          &registry, player, entt::null, movable.dominantDirection});
    }
  }
}

}  // namespace wanderer::sys::input
