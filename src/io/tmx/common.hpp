#pragma once

#include <centurion.hpp>  // fpoint
#include <string_view>    // string_view
#include <vector>         // vector

#include "common/maybe.hpp"
#include "common/tile_id.hpp"
#include "io/tmx/parse_ir.hpp"

namespace wanderer::io {

using tile_data = rune::tmx_data::gid_data;

[[nodiscard]] auto find_tile(const std::vector<ir::tileset>& tilesets, tile_id id)
    -> maybe<ir::tile>;

[[nodiscard]] auto get_tileset_offset(const ir::level& data, std::string_view tileset)
    -> int;

[[nodiscard]] auto get_tileset_tile_size(const ir::level& data, std::string_view tileset)
    -> maybe<cen::iarea>;

[[nodiscard]] auto make_depth_drawable(const ir::tile& tile,
                                       const cen::fpoint& pos,
                                       const cen::farea& size,
                                       int layer) -> ir::drawable;

}  // namespace wanderer::io
