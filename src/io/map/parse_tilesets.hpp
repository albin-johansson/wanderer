#pragma once

#include <filesystem>  // path
#include <rune.hpp>    // tmx_tileset
#include <vector>      // vector

#include "io/map/parse_ir.hpp"

namespace wanderer {

[[nodiscard]] auto parse_tilesets(const std::vector<rune::tmx_tileset>& tilesets,
                                  const std::filesystem::path& directory)
    -> std::vector<ir::tileset>;

}  // namespace wanderer
