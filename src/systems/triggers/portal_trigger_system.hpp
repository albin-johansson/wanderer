#pragma once

#include <entt.hpp>  // registry

namespace wanderer::sys {

/// \name Movement
/// \{

/**
 * \brief Updates all of the portal triggers in the level.
 *
 * \ingroup systems
 *
 * \param registry the current level registry.
 */
void update_portal_triggers(entt::registry& registry);

/// \} End of movement

}  // namespace wanderer::sys
