#pragma once

#include <filesystem>  // path

namespace wanderer {

// Returns the path to the directory used for storing persistent files
[[nodiscard]] auto files_directory() -> const std::filesystem::path&;

}  // namespace wanderer
