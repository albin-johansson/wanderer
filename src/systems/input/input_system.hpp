#pragma once

#include <centurion.hpp>
#include <entt.hpp>

#include "input.hpp"
#include "player.hpp"

namespace wanderer::sys {

/**
 * \brief Handles the current player input.
 *
 * \pre The player entity must have `Binds` and `Movable` components.
 *
 * \param registry the current registry.
 * \param dispatcher the event dispatcher that is being used.
 * \param input the current input state.
 */
void update_input(entt::registry& registry,
                  entt::dispatcher& dispatcher,
                  comp::player::entity player,
                  const input& input);

}  // namespace wanderer::sys
