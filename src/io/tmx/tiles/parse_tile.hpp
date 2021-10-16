#pragma once

#include <rune/everything.hpp>  // tmx_tile, tmx_tileset

#include "common/texture_id.hpp"
#include "common/tile_id.hpp"
#include "io/tmx/parse_ir.hpp"

namespace wanderer::io {

[[nodiscard]] auto make_tile(tile_id id,
                             int index,
                             texture_id texture,
                             const rune::tmx_tileset& tileset) -> ir::tile;

[[nodiscard]] auto parse_fancy_tile(ir::tileset& data,
                                    const rune::tmx_tile& tile,
                                    tile_id firstGid) -> ir::fancy_tile;

}  // namespace wanderer::io