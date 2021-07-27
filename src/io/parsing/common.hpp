#pragma once

#include <centurion.hpp>  // fpoint
#include <string_view>    // string_view
#include <vector>         // vector

#include "core/aliases/maybe.hpp"
#include "core/aliases/tile_id.hpp"
#include "io/parsing/parse_ir.hpp"

namespace wanderer::io {

using tile_data = rune::tmx_data::gid_data;

[[nodiscard]] auto find_tile(const std::vector<ir::tileset>& tilesets, tile_id id)
    -> maybe<ir::tile>;

[[nodiscard]] auto get_tileset_offset(const ir::level& data, std::string_view tileset)
    -> int;

[[nodiscard]] auto make_depth_drawable(const ir::tile& tile,
                                       const cen::fpoint& pos,
                                       const cen::farea& size,
                                       int layer) -> ir::depth_drawable;

}  // namespace wanderer::io
