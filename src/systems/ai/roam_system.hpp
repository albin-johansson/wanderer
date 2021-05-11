#pragma once

#include <entt.hpp>  // registry
#include <rune.hpp>  // delta_time

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
void update_roaming(entt::registry& registry, rune::delta_time dt);

/// \} End of AI

}  // namespace wanderer::sys
