#pragma once

#include <centurion.hpp>
#include <entt.hpp>

#include "player.hpp"

namespace wanderer::sys {

/**
 * \brief Handles the current player input.
 *
 * \pre The player entity must have `Binds` and `Movable` components.
 *
 * \param registry the current registry.
 * \param dispatcher the event dispatcher that is being used.
 * \param player the player entity.
 * \param keyState the current keyboard input state.
 */
void update_input(entt::registry& registry,
                  entt::dispatcher& dispatcher,
                  comp::player::entity player,
                  const cen::key_state& keyState);

}  // namespace wanderer::sys
