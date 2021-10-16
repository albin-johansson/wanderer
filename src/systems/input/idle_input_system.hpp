#pragma once

#include <entt.hpp>             // registry, dispatcher
#include <rune/everything.hpp>  // input

#include "components/ctx/binds.hpp"

namespace wanderer::sys {

/// \name Input
/// \{

/**
 * \brief Handles the player input if the player is idle.
 *
 * \ingroup systems
 *
 * \param registry the associated registry.
 * \param dispatcher the dispatcher used for events.
 * \param input the current input state.
 * \param binds the current input binds.
 */
void handle_idle_input(entt::registry& registry,
                       entt::dispatcher& dispatcher,
                       const rune::input& input,
                       const ctx::Binds& binds);

/// \} End of input

}  // namespace wanderer::sys
