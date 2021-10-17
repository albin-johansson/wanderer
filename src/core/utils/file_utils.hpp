#pragma once

#include <filesystem>  // path
#include <string>      // string

namespace wanderer {

/**
 * \brief Returns a textual representation of the time that the specified file was
 * modified.
 *
 * \ingroup core
 *
 * \param path the file that will be checked.
 *
 * \return a textual representation of the last write time of the specified file.
 */
[[nodiscard]] auto GetLastModified(const std::filesystem::path& path) -> std::string;

}  // namespace wanderer
