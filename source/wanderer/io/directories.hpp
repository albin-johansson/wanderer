#pragma once

#include <filesystem>  // path

namespace wanderer {

/**
 * \brief Returns the path to the directory used for storing persistent files.
 *
 * \return the persistent file directory.
 */
[[nodiscard]] auto get_persistent_file_dir() -> const std::filesystem::path&;

/**
 * \brief Returns the path to the persistent save directory.
 *
 * \return the persistent save file directory.
 */
[[nodiscard]] auto get_saves_dir() -> const std::filesystem::path&;

}  // namespace wanderer
