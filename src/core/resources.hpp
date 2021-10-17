#pragma once

#include <string>  // string

#include "common/cstr.hpp"

/// \namespace wanderer::resources
/// \brief Contains utilities for obtaining resource paths.
/// \ingroup core
namespace wanderer::resources {

/**
 * \brief Returns the file path for a texture with the specified name.
 *
 * \ingroup core
 *
 * \param resource the name of the resource.
 *
 * \return the path of the texture.
 */
[[nodiscard]] auto texture(CStr resource) -> std::string;

/**
 * \brief Returns the file path for a font with the specified name.
 *
 * \ingroup core
 *
 * \param resource the name of the resource.
 *
 * \return the path of the font.
 */
[[nodiscard]] auto font(CStr resource) -> std::string;

/**
 * \brief Returns the file path for a sound with the specified name.
 *
 * \ingroup core
 *
 * \param resource the name of the resource.
 *
 * \return the path of the sound.
 */
[[nodiscard]] auto sound(CStr resource) -> std::string;

/**
 * \brief Returns the file path for a map with the specified name.
 *
 * \ingroup core
 *
 * \param resource the name of the resource.
 *
 * \return the path of the map.
 */
[[nodiscard]] auto map(CStr resource) -> std::string;

}  // namespace wanderer::resources
