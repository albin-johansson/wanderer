#pragma once

#include <entt.hpp>  // registry, dispatcher

#include "components/ctx/binds.hpp"
#include "components/ctx/player.hpp"
#include "core/input.hpp"

namespace wanderer::sys {

/**
 * \brief Handles the current player input.
 *
 * \param registry the current registry.
 * \param dispatcher the event dispatcher that is being used.
 * \param input the current input state.
 * \param binds the current input binds.
 */
void update_input(entt::registry& registry,
                  entt::dispatcher& dispatcher,
                  const input& input,
                  const ctx::binds& binds);

/**
 * \brief Handles the player input if the player is idle.
 *
 * \param registry the associated registry.
 * \param dispatcher the dispatcher used for events.
 * \param input the current input state.
 * \param binds the current input binds.
 */
void handle_idle_input(entt::registry& registry,
                       entt::dispatcher& dispatcher,
                       const input& input,
                       const ctx::binds& binds);

/**
 * \brief Handles the player input if the player is moving.
 *
 * \param registry the current registry.
 * \param dispatcher the event dispatcher that is being used.
 * \param input the current input state.
 * \param binds the current input binds.
 */
void handle_move_input(entt::registry& registry,
                       entt::dispatcher& dispatcher,
                       const input& input,
                       const ctx::binds& binds);

}  // namespace wanderer::sys
