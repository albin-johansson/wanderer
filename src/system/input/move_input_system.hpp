#pragma once

#include <cen/key_state.hpp>
#include <entt.hpp>

#include "component/player.hpp"

namespace wanderer::sys::input {

/**
 * \brief Handles the player input if the player is moving.
 *
 * \note This method has no effect if the player entity doesn't have a
 * `humanoid_move` component.
 *
 * \pre The player entity must feature `Movable` and `Binds` components.
 *
 * \param registry the current registry.
 * \param dispatcher the event dispatcher that is being used.
 * \param player the player entity.
 * \param keyState the current keyboard input state.
 */
void handle_move_input(entt::registry& registry,
                       entt::dispatcher& dispatcher,
                       comp::player::entity player,
                       const cen::key_state& keyState);

}  // namespace wanderer::sys::input
