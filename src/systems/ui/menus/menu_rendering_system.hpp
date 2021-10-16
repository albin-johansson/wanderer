#pragma once

#include <entt.hpp>  // registry

namespace wanderer::sys {

/// \name Menus
/// \{

/**
 * \brief Renders the currently active menu.
 *
 * \ingroup systems
 *
 * \param shared the menu registry.
 */
void render_active_menu(const entt::registry& shared);

/// \} End of menus

}  // namespace wanderer::sys
