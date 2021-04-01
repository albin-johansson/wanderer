#pragma once

#include <entt.hpp>  // registry, dispatcher

#include "binds.hpp"
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
 * \param binds the current input binds.
 */
void update_input(entt::registry& registry,
                  entt::dispatcher& dispatcher,
                  comp::player::entity player,
                  const input& input,
                  const comp::binds& binds);

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
 * \param binds the current input binds.
 */
void handle_idle_input(entt::registry& registry,
                       entt::dispatcher& dispatcher,
                       comp::player::entity player,
                       const input& input,
                       const comp::binds& binds);

/**
 * \brief Handles the player input if the player is moving.
 *
 * \pre `player` must feature a `movable` component.
 * \pre `player` must feature a `binds` component.
 * \pre `player` must feature a `humanoid_move` component.
 *
 * \param registry the current registry.
 * \param dispatcher the event dispatcher that is being used.
 * \param player the player entity.
 * \param input the current input state.
 * \param binds the current input binds.
 */
void handle_move_input(entt::registry& registry,
                       entt::dispatcher& dispatcher,
                       comp::player::entity player,
                       const input& input,
                       const comp::binds& binds);

}  // namespace wanderer::sys
