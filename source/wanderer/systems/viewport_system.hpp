#pragma once

#include <entt/entt.hpp>

#include "wanderer/common.hpp"

namespace wanderer::sys {

/**
 * \ingroup systems
 * \defgroup viewport-system Viewport system
 */

/// \addtogroup viewport-system
/// \{

/**
 * \brief Updates the tilemap render bounds for a level registry.
 *
 * \param registry the current level registry.
 */
void update_render_bounds(entt::registry& registry);

/**
 * \brief Updates the viewport state.
 *
 * \param registry the current level registry.
 * \param dt the current delta time.
 */
void update_viewport(entt::registry& registry, float32 dt);

/// \} End of group viewport-system

}  // namespace wanderer::sys