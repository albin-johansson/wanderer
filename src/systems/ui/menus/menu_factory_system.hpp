#pragma once

#include <entt.hpp>  // registry, entity
#include <string>    // string

#include "components/ui/menu.hpp"
#include "core/menu_id.hpp"

namespace wanderer::sys {

/// \name Menus
/// \{

/// Creates a menu entity
auto MakeMenu(entt::registry& registry,
              std::string title,
              MenuId id,
              bool blocking = true) -> entt::entity;

/**
 * \brief Creates the home menu.
 *
 * \ingroup systems
 *
 * \param registry the menu registry.
 *
 * \return the created entity.
 */
auto MakeHomeMenu(entt::registry& registry) -> entt::entity;

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

/**
 * \brief Creates the controls menu.
 *
 * \ingroup systems
 *
 * \param registry the menu registry.
 *
 * \return the created entity.
 */
auto MakeControlsMenu(entt::registry& registry) -> entt::entity;

/**
 * \brief Creates the in-game menu.
 *
 * \ingroup systems
 *
 * \param registry the menu registry.
 *
 * \return the created entity.
 */
auto MakeInGameMenu(entt::registry& registry) -> entt::entity;

/// \} End of menus

}  // namespace wanderer::sys
