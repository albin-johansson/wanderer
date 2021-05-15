#pragma once

#include <filesystem>  // path

#include "components/map/level.hpp"

namespace wanderer::sys {

/// \name Levels
/// \{

/**
 * \brief Saves a level as a binary save file.
 *
 * \ingroup systems
 *
 * \param level the level that will be saved.
 * \param path the file path of the binary save file that will be created.
 */
void save(const comp::level& level, const std::filesystem::path& path);

/// \} End of levels

}  // namespace wanderer::sys
