#pragma once

#include <cen/key_state.hpp>
#include <entt.hpp>

namespace wanderer::sys::input {

/**
 * @brief Handles the player input if the player is idle.
 *
 * @note This method has no effect if the player entity doesn't have a
 * `humanoid_idle` component.
 *
 * @pre The player entity must feature a `Binds` component.
 *
 * @param registry the associated registry.
 * @param dispatcher the dispatcher used for events.
 * @param player the player entity.
 * @param keyState the current keyboard input state.
 */
void handle_idle_input(entt::registry& registry,
                       entt::dispatcher& dispatcher,
                       entt::entity player,
                       const cen::key_state& keyState);

}  // namespace wanderer::sys::input
