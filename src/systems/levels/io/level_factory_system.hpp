#pragma once

#include <filesystem>  // path

#include "components/map/level.hpp"
#include "core/graphics/graphics_context.hpp"
#include "io/parsing/parse_ir.hpp"

namespace wanderer::sys {

/// \name Levels
/// \{

/**
 * \brief Creates a level based on a parsed tilemap file.
 *
 * \ingroup systems
 *
 * \param data the parsed tilemap data.
 * \param graphics the graphics context used when loading textures.
 *
 * \return the created level.
 */
[[nodiscard]] auto make_level(const ir::level& data, graphics_context& graphics)
    -> comp::level;

/**
 * \brief Restores a level from a binary save file.
 *
 * \ingroup systems
 *
 * \param path the file path of the binary save file.
 * \param graphics the graphics context used when loading textures.
 *
 * \return the parsed level.
 */
[[nodiscard]] auto restore_level(const std::filesystem::path& path,
                                 graphics_context& graphics) -> comp::level;

/// \} End of levels

}  // namespace wanderer::sys
