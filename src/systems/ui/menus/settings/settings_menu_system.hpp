#pragma once

#include <entt.hpp>  // registry

namespace wanderer::sys {

/// \name Menus
/// \{

/**
 * \brief Synchronizes the state of settings UI components with the actual settings.
 *
 * \ingroup systems
 *
 * \param registry the menu registry.
 */
void SyncSettingsMenu(entt::registry& registry);

/// \} End of menus

}  // namespace wanderer::sys
