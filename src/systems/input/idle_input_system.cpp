#include "idle_input_system.hpp"

#include <cassert>   // assert
#include <optional>  // optional

#include "components/binds.hpp"
#include "components/humanoid.hpp"
#include "components/inventory.hpp"
#include "components/player.hpp"
#include "core/direction.hpp"
#include "core/ecs/registry_utils.hpp"
#include "events/humanoid_events.hpp"
#include "events/interact_event.hpp"

namespace wanderer::sys {
namespace {

[[nodiscard]] auto GetDirection(const cen::keyboard& keyboard,
                                const ctx::Binds& binds) noexcept
    -> std::optional<Direction>
{
  const auto left = keyboard.is_pressed(binds.left);
  const auto right = keyboard.is_pressed(binds.right);
  const auto up = keyboard.is_pressed(binds.up);
  const auto down = keyboard.is_pressed(binds.down);

  if (left) {
    return Direction::Left;
  }
  else if (right) {
    return Direction::Right;
  }
  else if (up) {
    return Direction::Up;
  }
  else if (down) {
    return Direction::Down;
  }
  else {
    return std::nullopt;
  }
}

void CheckForMovement(entt::registry& registry,
                      entt::dispatcher& dispatcher,
                      const cen::keyboard& keyboard,
                      const ctx::Binds& binds)
{
  if (const auto dir = GetDirection(keyboard, binds)) {
    const auto player = singleton_entity<Player>(registry);
    dispatcher.enqueue<BeginHumanoidMoveEvent>(registry, player, *dir);
  }
}

}  // namespace

void HandleIdleInput(entt::registry& registry,
                     entt::dispatcher& dispatcher,
                     const cen::keyboard& keyboard,
                     const ctx::Binds& binds)
{
  const auto player = singleton_entity<Player>(registry);
  assert(registry.all_of<HumanoidIdle>(player));

  if (keyboard.just_released(binds.interact)) {
    dispatcher.enqueue<InteractEvent>(registry, dispatcher);
  }
  else if (registry.empty<ActiveInventory>()) {
    if (keyboard.is_pressed(binds.attack)) {
      // FIXME
      dispatcher.enqueue<BeginAttackEvent>(registry, player, entt::null, Direction::Down);
    }
    else {
      CheckForMovement(registry, dispatcher, keyboard, binds);
    }
  }
}

}  // namespace wanderer::sys
