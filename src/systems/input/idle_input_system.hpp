#pragma once

#include <entt.hpp>  // registry, dispatcher

#include "components/ctx/binds.hpp"
#include "core/input.hpp"

namespace wanderer::sys {

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

}  // namespace wanderer::sys
