#pragma once

#include <rune/everything.hpp>  // tmx_tile, tmx_tileset

#include "io/tmx/parse_ir.hpp"
#include "wanderer_std.hpp"

namespace wanderer::io {

[[nodiscard]] auto make_tile(TileID id,
                             int index,
                             rune::texture_id texture,
                             const rune::tmx_tileset& tileset) -> ir::tile;

[[nodiscard]] auto parse_fancy_tile(ir::tileset& data,
                                    const rune::tmx_tile& tile,
                                    TileID firstGid) -> ir::fancy_tile;

}  // namespace wanderer::io