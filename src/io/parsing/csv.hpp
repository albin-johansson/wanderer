#pragma once

#include <string>  // string, getline
#include <vector>  // vector

namespace wanderer::io {

[[nodiscard]] auto parse_csv(const std::string& str) -> std::vector<std::string>;

}  // namespace wanderer::io
