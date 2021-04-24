#pragma once

#include <entt.hpp>  // registry

#include "core/graphics/graphics_context.hpp"

namespace wanderer::sys {

/// \name Menus
/// \{

/**
 * \brief Renders the currently active menu.
 *
 * \ingroup systems
 *
 * \param registry the menu registry.
 * \param graphics the graphics context that will be used.
 */
void render_active_menu(const entt::registry& registry, graphics_context& graphics);

/// \} End of menus

}  // namespace wanderer::sys
