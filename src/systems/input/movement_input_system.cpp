#include "movement_input_system.hpp"

#include <cassert>  // assert

#include "components/ctx/binds.hpp"
#include "components/ctx/player.hpp"
#include "components/humanoid_state.hpp"
#include "components/movable.hpp"
#include "core/direction.hpp"
#include "events/begin_attack_event.hpp"
#include "events/end_humanoid_move_event.hpp"
#include "events/interact_event.hpp"

namespace wanderer::sys {
namespace {

void move(comp::movable& movable, const direction dir) noexcept
{
  switch (dir)
  {
    case direction::right: {
      movable.velocity.x = movable.speed;
      break;
    }
    case direction::left: {
      movable.velocity.x = -movable.speed;
      break;
    }
    case direction::up: {
      movable.velocity.y = -movable.speed;
      break;
    }
    case direction::down: {
      movable.velocity.y = movable.speed;
      break;
    }
  }
  movable.velocity.normalize();
  movable.velocity.scale(movable.speed);
}

void stop(comp::movable& movable, const direction dir) noexcept
{
  switch (dir)
  {
    case direction::right:
      [[fallthrough]];
    case direction::left: {
      movable.velocity.x = 0;
      break;
    }
    case direction::up:
      [[fallthrough]];
    case direction::down: {
      movable.velocity.y = 0;
      break;
    }
  }
  movable.velocity.normalize();
  movable.velocity.scale(movable.speed);
}

[[nodiscard]] auto check_pressed(comp::movable& movable,
                                 const cen::keyboard& keyboard,
                                 const ctx::binds& binds) noexcept -> bool
{
  const auto left = keyboard.is_pressed(binds.left);
  const auto right = keyboard.is_pressed(binds.right);
  const auto up = keyboard.is_pressed(binds.up);
  const auto down = keyboard.is_pressed(binds.down);

  if (left && right)
  {
    stop(movable, direction::left);
    stop(movable, direction::right);
  }
  else if (left)
  {
    move(movable, direction::left);
  }
  else if (right)
  {
    move(movable, direction::right);
  }

  if (up && down)
  {
    stop(movable, direction::up);
    stop(movable, direction::down);
  }
  else if (up)
  {
    move(movable, direction::up);
  }
  else if (down)
  {
    move(movable, direction::down);
  }

  return up || down || right || left;
}

void check_released(comp::movable& movable,
                    const cen::keyboard& keyboard,
                    const ctx::binds& binds) noexcept
{
  if (keyboard.just_released(binds.left))
  {
    stop(movable, direction::left);
  }

  if (keyboard.just_released(binds.right))
  {
    stop(movable, direction::right);
  }

  if (keyboard.just_released(binds.up))
  {
    stop(movable, direction::up);
  }

  if (keyboard.just_released(binds.down))
  {
    stop(movable, direction::down);
  }
}

}  // namespace

void handle_move_input(entt::registry& registry,
                       entt::dispatcher& dispatcher,
                       const rune::input& input,
                       const ctx::binds& binds)
{
  const auto player = registry.ctx<ctx::player>().entity;
  assert(registry.all_of<comp::humanoid_move>(player));

  auto& movable = registry.get<comp::movable>(player);
  const auto& keyboard = input.keyboard;

  const auto areMoveKeysDown = check_pressed(movable, keyboard, binds);
  check_released(movable, keyboard, binds);

  if (!areMoveKeysDown && movable.velocity.is_zero())
  {
    dispatcher.enqueue<end_humanoid_move_event>(registry, player);
  }
  else if (keyboard.is_pressed(binds.attack))
  {
    movable.velocity.reset();

    // FIXME null weapon
    dispatcher.enqueue<begin_attack_event>(registry, player, entt::null, movable.dir);
  }
  else if (keyboard.just_released(binds.interact))
  {
    dispatcher.enqueue<interact_event>(registry, dispatcher);
  }
}

}  // namespace wanderer::sys
