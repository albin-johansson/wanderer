#pragma once

#include <entt/entt.hpp>  // registry

#include "core/graphics/graphics_context.hpp"

namespace wanderer::sys {

/// \name Labels
/// \{

/**
 * \brief Renders all labels associated with the active menu.
 *
 * \ingroup systems
 *
 * \param registry the menu registry.
 * \param graphics the graphics context that will be used.
 */
void RenderLabels(const entt::registry& registry, GraphicsContext& graphics);

/// \} End of labels

}  // namespace wanderer::sys
