#pragma once

#include <filesystem>  // path
#include <rune.hpp>    // tmx_tilesets
#include <vector>      // vector

#include "io/parsing/parse_ir.hpp"

namespace wanderer::io {

[[nodiscard]] auto parse_tilesets(const rune::tmx_tilesets& tilesets,
                                  const std::filesystem::path& directory)
    -> std::vector<ir::tileset>;

}  // namespace wanderer::io
