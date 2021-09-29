#pragma once

#include <entt.hpp>  // registry

#include "components/ui/menu.hpp"

namespace wanderer::sys {

/// \name Menus
/// \{

/**
 * \brief Creates and returns a saves menu entity.
 *
 * \ingroup systems
 *
 * \param registry the menu registry.
 *
 * \return the created entity.
 */
auto make_saves_menu(entt::registry& registry) -> entt::entity;

/// \} End of menus

}  // namespace wanderer::sys
