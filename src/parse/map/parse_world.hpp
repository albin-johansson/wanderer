#pragma once

#include <filesystem>  // path

#include "graphics_context.hpp"
#include "parse_ir.hpp"

namespace wanderer {

/**
 * \brief Parses a save file and returns the corresponding world data.
 *
 * \details This function expects that the paths of any potential levels in the
 * world are relative to the main world file.
 *
 * \param world the file path of the world JSON-file.
 * \param graphics the graphics context that will be used.
 *
 * \return an intermediate representation of the game world.
 */
[[nodiscard]] auto parse_world(const std::filesystem::path& world,
                               graphics_context& graphics) -> ir::world;

}  // namespace wanderer
