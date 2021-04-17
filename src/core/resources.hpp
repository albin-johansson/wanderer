#pragma once

#include <centurion.hpp>  // czstring
#include <string>         // string

/// \namespace wanderer::resources
/// \brief Contains utilities for obtaining resource paths.
/// \ingroup core
namespace wanderer::resources {

/// \addtogroup core
/// \{

/**
 * \brief Returns the file path for a texture with the specified name.
 *
 * \param resource the name of the resource.
 *
 * \return the path of the texture.
 */
[[nodiscard]] auto texture(cen::czstring resource) -> std::string;

/**
 * \brief Returns the file path for a font with the specified name.
 *
 * \param resource the name of the resource.
 *
 * \return the path of the font.
 */
[[nodiscard]] auto font(cen::czstring resource) -> std::string;

/**
 * \brief Returns the file path for a sound with the specified name.
 *
 * \param resource the name of the resource.
 *
 * \return the path of the sound.
 */
[[nodiscard]] auto sound(cen::czstring resource) -> std::string;

/**
 * \brief Returns the file path for a map with the specified name.
 *
 * \param resource the name of the resource.
 *
 * \return the path of the map.
 */
[[nodiscard]] auto map(cen::czstring resource) -> std::string;

/// \} End of group core

}  // namespace wanderer::resources
