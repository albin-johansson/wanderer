#pragma once

#include <centurion.hpp>  // keyboard
#include <entt.hpp>       // registry, dispatcher

#include "components/binds.hpp"

namespace wanderer::sys {

/// \name Input
/// \{

/// \brief Handles the player input if the player is idle.
/// \ingroup systems
void HandleIdleInput(entt::registry& registry,
                     entt::dispatcher& dispatcher,
                     const cen::keyboard& keyboard,
                     const ctx::Binds& binds);

/// \} End of input

}  // namespace wanderer::sys
