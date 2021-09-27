#pragma once

#include <entt.hpp>  // registry

#include "core/graphics/graphics_context.hpp"

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
 * \note Make sure to call `sys::sort_depth_drawables()` before calling this function.
 *
 * \param registry the current level registry.
 * \param graphics the graphics context that will be used.
 *
 * \since 0.1.0
 */
void render_drawables(const entt::registry& registry, graphics_context& graphics);

/// \} End of drawables

}  // namespace wanderer::sys
