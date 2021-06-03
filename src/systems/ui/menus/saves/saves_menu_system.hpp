#pragma once

#include <entt.hpp>  // registry
#include <string>    // string

namespace wanderer::sys {

/// \name Menus
/// \{

/**
 * \brief Refreshes the state of the saves menu.
 *
 * \details This function updates the saves menu by fetching the currently available save
 * files.
 *
 * \ingroup systems
 *
 * \param registry the menu registry.
 */
void refresh_saves_menu(entt::registry& registry);

/**
 * \brief Updates the save file preview.
 *
 * \details This destroys the current temporary entities used for save file previews, and
 * replaces them with new ones based on the currently selected save file.
 *
 * \pre The saves menu must be active.
 *
 * \ingroup systems
 *
 * \param registry the menu registry.
 */
void change_save_preview(entt::registry& registry);

/**
 * \brief Changes the current save file page to the next one.
 *
 * \ingroup systems
 *
 * \param registry the menu registry.
 */
void increment_saves_button_group_page(entt::registry& registry);

/**
 * \brief Changes the current save file page to the previous one.
 *
 * \ingroup systems
 *
 * \param registry the menu registry.
 */
void decrement_saves_button_group_page(entt::registry& registry);

/**
 * \brief Returns the name of the currently selected save file.
 *
 * \pre There must be a selected save entry by the time this function is called.
 *
 * \ingroup systems
 *
 * \param shared the shared data registry.
 *
 * \return the name of the currently selected save name.
 */
[[nodiscard]] auto get_selected_save_name(entt::registry& shared) -> std::string;

/// \} End of menus

}  // namespace wanderer::sys
