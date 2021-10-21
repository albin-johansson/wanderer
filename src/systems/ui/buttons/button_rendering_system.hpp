#pragma once

#include <entt.hpp>  // registry

#include "components/ui/button.hpp"
#include "components/ui/button_group.hpp"
#include "core/graphics/graphics_context.hpp"

namespace wanderer::sys {

/// \name Buttons
/// \{

/**
 * \brief Renders all buttons in the currently active menu.
 *
 * \ingroup systems
 *
 * \param registry the menu registry.
 * \param graphics the graphics context that will be used.
 */
void RenderButtons(const entt::registry& registry, GraphicsContext& graphics);

/**
 * \brief Renders visual cues for the enabled buttons in button groups in the currently
 * active menu.
 *
 * \ingroup systems
 *
 * \param registry the menu registry.
 * \param graphics the graphics context that will be used.
 */
void RenderButtonGroupIndicators(const entt::registry& registry,
                                 GraphicsContext& graphics);

/// \} End of buttons

}  // namespace wanderer::sys
