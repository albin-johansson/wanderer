#pragma once

#include <filesystem>  // path

namespace wanderer {

/// Returns the path to the directory used for storing persistent files
[[nodiscard]] auto GetFilesDirectory() -> const std::filesystem::path&;

/// Returns the path to the directory used for storing save files
[[nodiscard]] auto GetSavesDirectory() -> const std::filesystem::path&;

}  // namespace wanderer
