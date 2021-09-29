#pragma once

#include <entt.hpp>  // registry, entity
#include <string>    // string

#include "components/ui/button.hpp"
#include "core/grid_position.hpp"
#include "core/menu_action.hpp"

namespace wanderer::sys {

/// \name Buttons
/// \{

/**
 * \brief Adds button components to an existing entity.
 *
 * \details The supplied entity will have `button` and `button_drawable` components added
 * to it.
 *
 * \ingroup systems
 *
 * \param registry the menu registry.
 * \param entity the entity that will have button components added to it.
 * \param text the text of the button.
 * \param action the action that will be associated with the button.
 * \param position the position of the button.
 */
void add_button(entt::registry& registry,
                entt::entity entity,
                std::string text,
                menu_action action,
                grid_position position);

/**
 * \brief Creates a button.
 *
 * \details The entity will feature `button` and `button_drawable` components.
 *
 * \ingroup systems
 *
 * \param registry the menu registry.
 * \param text the text of the button.
 * \param action the action that will be associated with the button.
 * \param position the position of the button.
 *
 * \return the created entity.
 */
auto make_button(entt::registry& registry,
                 std::string text,
                 menu_action action,
                 grid_position position) -> entt::entity;

/// \} End of buttons

}  // namespace wanderer::sys
