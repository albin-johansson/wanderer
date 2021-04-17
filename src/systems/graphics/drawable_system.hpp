#pragma once

#include <entt.hpp>  // registry

#include "core/graphics/graphics_context.hpp"

namespace wanderer::sys {

/// \name Drawables
/// \{

void update_drawables(entt::registry& registry);

/**
 * \brief Renders all drawable objects.
 *
 * \note Make sure to call `sys::update_depth()` before calling this function.
 *
 * \param registry the current level registry.
 * \param graphics the graphics context that will be used.
 *
 * \since 0.1.0
 */
void render_drawables(const entt::registry& registry, graphics_context& graphics);

/// \} End of drawables

}  // namespace wanderer::sys
