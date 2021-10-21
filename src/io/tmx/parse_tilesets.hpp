#pragma once

#include <filesystem>  // path
#include <vector>      // vector

#include <rune/everything.hpp>  // tmx_tilesets

#include "io/tmx/parse_ir.hpp"

namespace wanderer::io {

[[nodiscard]] auto parse_tilesets(const rune::tmx_tilesets& tilesets,
                                  const std::filesystem::path& directory)
    -> std::vector<ir::tileset>;

}  // namespace wanderer::io
