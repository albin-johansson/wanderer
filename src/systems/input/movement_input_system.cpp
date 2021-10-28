#include "movement_input_system.hpp"

#include <cassert>  // assert

#include "components/binds.hpp"
#include "components/humanoid.hpp"
#include "components/movable.hpp"
#include "components/player.hpp"
#include "core/direction.hpp"
#include "core/ecs/registry_utils.hpp"
#include "events/humanoid_events.hpp"
#include "events/interact_event.hpp"

namespace wanderer::sys {
namespace {

void Move(comp::Movable& movable, const Direction dir)
{
  switch (dir) {
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
  }

  movable.velocity = glm::normalize(movable.velocity);
  movable.velocity *= movable.speed;
}

void Stop(comp::Movable& movable, const Direction dir)
{
  switch (dir) {
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
  }

  if (!is_zero(movable.velocity)) {
    movable.velocity = glm::normalize(movable.velocity);
    movable.velocity *= movable.speed;
  }
}

[[nodiscard]] auto CheckPressed(comp::Movable& movable,
                                const cen::keyboard& keyboard,
                                const ctx::Binds& binds) noexcept -> bool
{
  const auto left = keyboard.is_pressed(binds.left);
  const auto right = keyboard.is_pressed(binds.right);
  const auto up = keyboard.is_pressed(binds.up);
  const auto down = keyboard.is_pressed(binds.down);

  if (left && right) {
    Stop(movable, Direction::Left);
    Stop(movable, Direction::Right);
  }
  else if (left) {
    Move(movable, Direction::Left);
  }
  else if (right) {
    Move(movable, Direction::Right);
  }

  if (up && down) {
    Stop(movable, Direction::Up);
    Stop(movable, Direction::Down);
  }
  else if (up) {
    Move(movable, Direction::Up);
  }
  else if (down) {
    Move(movable, Direction::Down);
  }

  return up || down || right || left;
}

void CheckReleased(comp::Movable& movable,
                   const cen::keyboard& keyboard,
                   const ctx::Binds& binds) noexcept
{
  if (keyboard.just_released(binds.left)) {
    Stop(movable, Direction::Left);
  }

  if (keyboard.just_released(binds.right)) {
    Stop(movable, Direction::Right);
  }

  if (keyboard.just_released(binds.up)) {
    Stop(movable, Direction::Up);
  }

  if (keyboard.just_released(binds.down)) {
    Stop(movable, Direction::Down);
  }
}

}  // namespace

void HandleMoveInput(entt::registry& registry,
                     entt::dispatcher& dispatcher,
                     const cen::keyboard& keyboard,
                     const ctx::Binds& binds)
{
  const auto player = singleton_entity<comp::Player>(registry);
  assert(registry.all_of<comp::HumanoidMove>(player));

  auto& movable = registry.get<comp::Movable>(player);

  const auto areMoveKeysDown = CheckPressed(movable, keyboard, binds);
  CheckReleased(movable, keyboard, binds);

  if (!areMoveKeysDown && is_zero(movable.velocity)) {
    dispatcher.enqueue<EndHumanoidMoveEvent>(registry, player);
  }
  else if (keyboard.is_pressed(binds.attack)) {
    movable.velocity.x = 0;
    movable.velocity.y = 0;

    // FIXME null weapon
    dispatcher.enqueue<BeginAttackEvent>(registry, player, entt::null, movable.dir);
  }
  else if (keyboard.just_released(binds.interact)) {
    dispatcher.enqueue<InteractEvent>(registry, dispatcher);
  }
}

}  // namespace wanderer::sys
