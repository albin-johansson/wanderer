#pragma once

#include <entt.hpp>  // registry, entity

namespace wanderer::sys {

/// \name Menus
/// \{

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
 * \brief Creates and returns a saves menu entity.
 *
 * \ingroup systems
 *
 * \param registry the menu registry.
 *
 * \return the created entity.
 */
auto MakeSavesMenu(entt::registry& registry) -> entt::entity;

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

auto MakeDevConsoleMenu(entt::registry& registry) -> entt::entity;

/// \} End of menus

}  // namespace wanderer::sys
