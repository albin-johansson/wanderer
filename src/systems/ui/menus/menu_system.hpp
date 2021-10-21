#pragma once

#include <entt.hpp>             // registry, dispatcher
#include <rune/everything.hpp>  // input

#include "core/menu_id.hpp"

namespace wanderer::sys {

/// \name Menus
/// \{

/**
 * \brief Updates the currently active menu.
 *
 * \ingroup systems
 *
 * \param registry the menu registry.
 * \param dispatcher the event dispatcher that will be used.
 * \param input the current input state.
 */
void UpdateMenu(entt::registry& registry,
                entt::dispatcher& dispatcher,
                const rune::input& input);

/**
 * \brief Changes the currently active menu.
 *
 * \ingroup systems
 *
 * \param registry the menu registry.
 * \param dispatcher the event dispatcher that will be used.
 * \param id the ID associated with the menu that will be selected.
 */
void SwitchMenu(entt::registry& registry, entt::dispatcher& dispatcher, MenuId id);

/**
 * \brief Indicates whether or not the current menu is blocking.
 *
 * \details A blocking menu is meant to prevent the game from updating.
 *
 * \ingroup systems
 *
 * \return `true` if the current menu is blocking; `false` otherwise
 */
[[nodiscard]] auto IsCurrentMenuBlocking(const entt::registry& registry) -> bool;

/// \} End of menus

}  // namespace wanderer::sys
