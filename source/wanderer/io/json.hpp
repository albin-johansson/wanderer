#pragma once

#include <nlohmann/json.hpp>

namespace wanderer {

[[nodiscard]] auto read_json(const std::filesystem::path& path) -> nlohmann::json;

}  // namespace wanderer
