#pragma once

#include <filesystem>  // path
#include <step_map.hpp>
#include <vector>  // vector

#include "parse_ir.hpp"

namespace wanderer {

using tileset_collection = std::vector<std::unique_ptr<step::tileset>>;

[[nodiscard]] auto parse_tilesets(const tileset_collection& tilesets,
                                  const std::filesystem::path& directory)
    -> std::vector<ir::tileset>;

}  // namespace wanderer
