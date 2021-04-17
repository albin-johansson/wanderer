#pragma once

#include <entt.hpp>  // registry

namespace wanderer::sys {

/// \name Settings
/// \{

/**
 * \brief Attempts to load the settings from the preferred file directory.
 *
 * \ingroup systems
 *
 * \details This function will look for a binds file called `settings.ini` in the
 * preferred file directory. The default settings will be used if no such file was found.
 *
 * \param registry the shared data registry to add the loaded settings to.
 */
void load_settings(entt::registry& registry);

/**
 * \brief Toggles the value of the "fullscreen" setting.
 *
 * \ingroup systems
 *
 * \param registry the shared data registry that contains the settings.
 *
 * \return the new value of the setting.
 */
auto toggle_fullscreen(entt::registry& registry) -> bool;

/**
 * \brief Toggles the value of the "integer scaling" setting.
 *
 * \ingroup systems
 *
 * \param registry the shared data registry that contains the settings.
 *
 * \return the new value of the setting.
 */
auto toggle_integer_scaling(entt::registry& registry) -> bool;

/**
 * \brief Toggles the value of the "simulate lights" setting.
 *
 * \ingroup systems
 *
 * \param registry the shared data registry that contains the settings.
 *
 * \return the new value of the setting.
 */
auto toggle_simulate_lights(entt::registry& registry) -> bool;

/**
 * \brief Updates the settings file in the preferred file directory.
 *
 * \ingroup systems
 *
 * \details This function will overwrite any current settings file in the preferred file
 * directory. This function is intended to be called just before the game is closed, since
 * it is of no use to continuously update the settings file.
 *
 * \param registry the shared data registry that contains the settings.
 */
void save_settings_before_exit(const entt::registry& registry);

/// \} End of settings

}  // namespace wanderer::sys
