/**
 * @brief Provides the system for dealing with idle player input.
 * @file idle_input_system.h
 * @author Albin Johansson
 * @copyright MIT License
 * @date 2020
 */

#pragma once

#include <entt.hpp>

#include "input.h"

namespace wanderer::sys::input {

/**
 * @brief Handles the player input when the player is idle.
 *
 * @note This method has no effect if the player entity doesn't have the
 * `HumanoidIdle`.
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
