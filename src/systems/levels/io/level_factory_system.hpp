#pragma once

#include <filesystem>  // path

#include "components/lvl/level.hpp"
#include "core/graphics/graphics_context.hpp"
#include "io/tmx/parse_ir.hpp"

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

/// \} End of levels

}  // namespace wanderer::sys
