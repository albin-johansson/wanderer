#pragma once

#include <entt.hpp>  // registry

#include "components/ui/menu.hpp"

namespace wanderer::sys {

/// \name Menus
/// \{

/**
 * \brief Creates the settings menu.
 *
 * \ingroup systems
 *
 * \param registry the menu registry.
 *
 * \return the created entity.
 */
auto MakeSettingsMenu(entt::registry& registry) -> entt::entity;

/// \} End of menus

}  // namespace wanderer::sys
