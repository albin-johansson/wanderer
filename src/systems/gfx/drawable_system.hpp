#pragma once

#include <entt.hpp>  // registry

namespace wanderer::sys {

/// \name Drawables
/// \{

/**
 * \brief Updates the destination rectangles of all drawables that are movable.
 *
 * \ingroup systems
 *
 * \param registry the current level registry.
 */
void update_drawables(entt::registry& registry);

/**
 * \brief Renders all drawable objects.
 *
 * \ingroup systems
 *
 * \note Make sure to call `sys::update_depth()` before calling this function.
 *
 * \param registry the current level registry.
 *
 * \since 0.1.0
 */
void render_drawables(const entt::registry& registry);

/// \} End of drawables

}  // namespace wanderer::sys
