#pragma once

#include <entt.hpp>             // registry, dispatcher
#include <rune/everything.hpp>  // input

#include "components/ctx/binds.hpp"
#include "components/player.hpp"

namespace wanderer::sys {

/// \name Input
/// \{

/**
 * \brief Handles the current player input.
 *
 * \ingroup systems
 *
 * \param registry the current level registry.
 * \param dispatcher the event dispatcher that will be used.
 * \param input the current input state.
 * \param binds the current input binds.
 */
void UpdateInput(entt::registry& registry,
                 entt::dispatcher& dispatcher,
                 const rune::input& input,
                 const ctx::Binds& binds);

/// \} End of input

}  // namespace wanderer::sys
