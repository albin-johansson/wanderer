#pragma once

#include <entt.hpp>  // registry

namespace wanderer::sys {

/// \name Debug
/// \{

/**
 * \brief Renders debug information, such as hitboxes and triggers.
 *
 * \ingroup systems
 *
 * \param registry the level registry.
 */
void render_debug_info(const entt::registry& registry);

/**
 * \brief Renders debug information for menus, such as the UI grid.
 *
 * \ingroup systems
 *
 * \param registry the menu registry.
 */
void render_menu_debug_info(const entt::registry& registry);

/// \} End of debug

}  // namespace wanderer::sys
