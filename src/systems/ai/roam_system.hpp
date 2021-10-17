#pragma once

#include <entt.hpp>             // registry
#include <rune/everything.hpp>  // delta_time

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
void UpdateRoaming(entt::registry& registry, float dt);

/// \} End of AI

}  // namespace wanderer::sys
