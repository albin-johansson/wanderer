#pragma once

#include <entt.hpp>
#include <input.hpp>

namespace wanderer::sys::input {

/**
 * @brief Handles the current player input.
 *
 * @pre The player entity must have `Binds` and `Movable` components.
 *
 * @param registry the current registry.
 * @param dispatcher the event dispatcher that is being used.
 * @param player the player entity.
 * @param input the current key and mouse state.
 */
void update(entt::registry& registry,
            entt::dispatcher& dispatcher,
            entt::entity player,
            const input& input);

}  // namespace wanderer::sys::input
