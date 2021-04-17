#pragma once

#include <entt.hpp>  // registry, dispatcher

#include "components/ctx/binds.hpp"
#include "core/input.hpp"

namespace wanderer::sys {

/// \name Input
/// \{

/**
 * \brief Handles the player input if the player is moving.
 *
 * \ingroup systems
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

/// \} End of input

}  // namespace wanderer::sys
