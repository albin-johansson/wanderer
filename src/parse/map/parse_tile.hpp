#pragma once

#include <step_map.hpp>

#include "parse_ir.hpp"
#include "texture_handle.hpp"
#include "tile_id.hpp"

namespace wanderer {

[[nodiscard]] auto make_tile(tile_id id,
                             int index,
                             const texture_handle& texture,
                             const step::tileset& tileset) -> ir::tile;

[[nodiscard]] auto parse_fancy_tile(ir::tileset& data,
                                    const ir::tile& tileData,
                                    const step::tile& tile,
                                    tile_id firstGid) -> ir::fancy_tile;

}  // namespace wanderer