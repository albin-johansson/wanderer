#pragma once

#include <centurion.hpp>
#include <entt.hpp>

#include "input.hpp"
#include "player.hpp"

namespace wanderer::sys {

/**
 * \brief Handles the player input if the player is idle.
 *
 * \pre `player` must feature a `binds` component.
 * \pre `player` must feature a `humanoid_idle` component.
 *
 * \param registry the associated registry.
 * \param dispatcher the dispatcher used for events.
 * \param player the player entity.
 * \param input the current input state.
 */
void handle_idle_input(entt::registry& registry,
                       entt::dispatcher& dispatcher,
                       comp::player::entity player,
                       const input& input);

}  // namespace wanderer::sys
