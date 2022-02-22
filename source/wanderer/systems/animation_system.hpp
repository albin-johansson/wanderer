#pragma once

#include <entt/entt.hpp>

#include "wanderer/common.hpp"

namespace wanderer::sys {

/**
 * \ingroup systems
 * \defgroup animation-system
 *
 * \brief Manages animation aspects.
 */

/// \addtogroup animation-system
/// \{

/**
 * \brief Updates the state of all animations.
 *
 * \param registry the current level registry.
 */
void update_animations(entt::registry& registry);

/// \} End of group animation-system

}  // namespace wanderer::sys