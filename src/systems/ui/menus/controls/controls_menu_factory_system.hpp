#pragma once

#include <entt.hpp>  // registry

#include "components/ui/menu.hpp"

namespace wanderer::sys {

/// \name Menus
/// \{

/**
 * \brief Creates the controls menu.
 *
 * \ingroup systems
 *
 * \param registry the menu registry.
 *
 * \return the created entity.
 */
auto make_controls_menu(entt::registry& registry) -> comp::menu::entity;

/// \} End of menus

}  // namespace wanderer::sys
