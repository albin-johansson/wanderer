#pragma once

#include <entt.hpp>  // registry

#include "core/graphics/graphics_context.hpp"

namespace wanderer::sys {

/// \name Lines
/// \{

/**
 * \brief Renders all lines in the currently active menu.
 *
 * \ingroup systems
 *
 * \param registry the menu registry.
 * \param graphics the graphics context that will be used.
 */
void render_lines(const entt::registry& registry, GraphicsContext& graphics);

/// \} End of lines

}  // namespace wanderer::sys