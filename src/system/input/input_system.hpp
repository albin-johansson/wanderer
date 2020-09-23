/**
 * @brief Provides the system for dealing with player input.
 * @file input_system.hpp
 * @author Albin Johansson
 * @copyright MIT License
 * @date 2020
 */

#pragma once

#include <input.hpp>

#include "wanderer_stdinc.hpp"

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
            const Input& input);

}  // namespace wanderer::sys::input
