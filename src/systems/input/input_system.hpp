#pragma once

#include <centurion.hpp>  // keyboard
#include <entt.hpp>       // registry, dispatcher

#include "components/binds.hpp"
#include "components/player.hpp"

namespace wanderer::sys {

/// \name Input
/// \{

/// \brief Handles the current player input.
/// \ingroup systems
void UpdateInput(entt::registry& registry,
                 entt::dispatcher& dispatcher,
                 const cen::keyboard& keyboard,
                 const ctx::Binds& binds);

/// \} End of input

}  // namespace wanderer::sys
