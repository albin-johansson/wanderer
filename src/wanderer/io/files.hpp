#pragma once

#include "wanderer/type/string.hpp"

namespace wanderer {

/// Reads the contents of a file into a plain string.
[[nodiscard]] auto load_file_into_string(const char* filename) -> String;

}  // namespace wanderer
