#pragma once

#include <filesystem>  // path

#include "components/map/level.hpp"

namespace wanderer::sys {

/// \brief Saves a level as a binary save file.
void save(const comp::level& level, const std::filesystem::path& path);

}  // namespace wanderer::sys
