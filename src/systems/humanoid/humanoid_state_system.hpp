#pragma once

#include <entt.hpp>  // registry, dispatcher

namespace wanderer::sys {

/// \name Humanoids
/// \{

/**
 * \brief Updates the state of all humanoids.
 *
 * \ingroup systems
 *
 * \param registry the current level registry.
 * \param dispatcher the dispatcher that will be used.
 */
void update_humanoid_states(entt::registry& registry, entt::dispatcher& dispatcher);

/// \} End of humanoid

}  // namespace wanderer::sys
