#include "input_system.hpp"

#include <cassert>   // assert
#include <optional>  // optional

#include "begin_attack_event.hpp"
#include "begin_humanoid_move_event.hpp"
#include "binds.hpp"
#include "direction.hpp"
#include "humanoid_state.hpp"
#include "interact_event.hpp"
#include "inventory.hpp"
#include "player.hpp"

namespace wanderer::sys {
namespace {

[[nodiscard]] auto get_direction(const cen::keyboard& keyboard,
                                 const comp::binds& binds) noexcept
    -> std::optional<direction>
{
  const auto left = keyboard.is_pressed(binds.left);
  const auto right = keyboard.is_pressed(binds.right);
  const auto up = keyboard.is_pressed(binds.up);
  const auto down = keyboard.is_pressed(binds.down);

  if (left)
  {
    return direction::left;
  }
  else if (right)
  {
    return direction::right;
  }
  else if (up)
  {
    return direction::up;
  }
  else if (down)
  {
    return direction::down;
  }
  else
  {
    return std::nullopt;
  }
}

void check_for_movement(entt::registry& registry,
                        entt::dispatcher& dispatcher,
                        const cen::keyboard& keyboard,
                        const comp::binds& binds,
                        const comp::player::entity player)
{
  if (const auto dir = get_direction(keyboard, binds))
  {
    dispatcher.enqueue<comp::begin_humanoid_move_event>(&registry, player, *dir);
  }
}

}  // namespace

void handle_idle_input(entt::registry& registry,
                       entt::dispatcher& dispatcher,
                       const comp::player::entity player,
                       const input& input,
                       const comp::binds& binds)
{
  assert(registry.has<comp::humanoid_idle>(player));
  const auto& keyboard = input.keyboard;

  if (keyboard.just_released(binds.interact))
  {
    dispatcher.enqueue<comp::interact_event>(&registry, &dispatcher, player);
  }
  else if (registry.empty<comp::active_inventory>())
  {
    if (keyboard.is_pressed(binds.attack))
    {
      // FIXME
      dispatcher.enqueue<comp::begin_attack_event>(&registry,
                                                   player,
                                                   entt::null,
                                                   direction::down);
    }
    else
    {
      check_for_movement(registry, dispatcher, input.keyboard, binds, player);
    }
  }
}

}  // namespace wanderer::sys
