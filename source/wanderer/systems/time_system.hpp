#pragma once

#include <entt/entt.hpp>

#include "wanderer/common.hpp"

namespace wanderer::sys {

/**
 * \ingroup systems
 * \defgroup time-system Time system
 */

/// \addtogroup time-system
/// \{

/**
 * \brief Updates the state of the in-game time.
 *
 * \param registry the level registry.
 * \param dispatcher the event dispatcher.
 * \param dt the delta time.
 */
void update_time(entt::registry& registry, entt::dispatcher& dispatcher, float32 dt);

/// \} End of group time-system

}  // namespace wanderer::sys
