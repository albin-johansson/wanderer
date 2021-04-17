#pragma once

#include <entt.hpp>  // registry

#include "core/graphics_context.hpp"

namespace wanderer::sys {

/**
 * \brief Renders debug information, such as hitboxes and triggers.
 *
 * \param registry the level registry.
 * \param graphics the graphics context that will be used.
 */
void render_debug_info(const entt::registry& registry, graphics_context& graphics);

/**
 * \brief Renders debug information for menus, such as the UI grid.
 *
 * \param registry the menu registry.
 * \param graphics the graphics context that will be used.
 */
void render_menu_debug_info(const entt::registry& registry, graphics_context& graphics);

}  // namespace wanderer::sys
