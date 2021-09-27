#pragma once

#include <entt.hpp>  // registry

#include "core/graphics/graphics_context.hpp"

namespace wanderer::sys {

/// \name Debug
/// \{

/**
 * \brief Renders debug information, such as hitboxes and triggers.
 *
 * \ingroup systems
 *
 * \param registry the level registry.
 * \param graphics the graphics context that will be used.
 */
void render_debug_info(const entt::registry& registry, graphics_context& graphics);

/**
 * \brief Renders debug information for menus, such as the UI grid.
 *
 * \ingroup systems
 *
 * \param registry the menu registry.
 * \param graphics the graphics context that will be used.
 */
void render_menu_debug_info(const entt::registry& registry, graphics_context& graphics);

/// \} End of debug

}  // namespace wanderer::sys
