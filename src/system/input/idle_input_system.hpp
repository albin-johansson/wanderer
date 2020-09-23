#pragma once

#include <entt.hpp>

#include "input.hpp"

namespace wanderer::sys::input {

/**
 * @brief Handles the player input if the player is idle.
 *
 * @note This method has no effect if the player entity doesn't have a
 * `HumanoidIdle` component.
 *
 * @pre The player entity must feature a `Binds` component.
 *
 * @param registry the associated registry.
 * @param dispatcher the dispatcher used for events.
 * @param player the player entity.
 * @param input the current mouse and key state.
 */
void handle_idle_input(entt::registry& registry,
                       entt::dispatcher& dispatcher,
                       entt::entity player,
                       const Input& input);

}  // namespace wanderer::sys::input
