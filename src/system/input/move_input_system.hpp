/**
 * @brief Provides the system for dealing with movement player input.
 * @file move_input_system.hpp
 * @author Albin Johansson
 * @copyright MIT License
 * @date 2020
 */

#pragma once

#include <entt.hpp>

#include "input.hpp"

namespace wanderer::sys::input {

/**
 * @brief Handles the player input if the player is moving.
 *
 * @note This method has no effect if the player entity doesn't have a
 * `humanoid_move` component.
 *
 * @pre The player entity must feature `Movable` and `Binds` components.
 *
 * @param registry the current registry.
 * @param dispatcher the event dispatcher that is being used.
 * @param player the player entity.
 * @param input the current key and mouse state.
 */
void handle_move_input(entt::registry& registry,
                       entt::dispatcher& dispatcher,
                       entt::entity player,
                       const Input& input);

}  // namespace wanderer::sys::input
