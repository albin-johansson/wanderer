#pragma once

#include <string>  // string

namespace wanderer {

// Returns the path to the directory used for storing persistent files
[[nodiscard]] auto files_directory() -> const std::string&;

}
