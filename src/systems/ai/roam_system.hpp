#pragma once

#include <entt.hpp>  // registry

#include "core/aliases/delta_time.hpp"

namespace wanderer::sys {

/// \name AI
/// \{

/**
 * \brief Updates entities with both `roam` and `movable` components.
 *
 * \ingroup systems
 *
 * \param registry the current level registry.
 * \param dt the current delta time.
 */
void update_roaming(entt::registry& registry, delta_time dt);

/// \} End of AI

}  // namespace wanderer::sys
