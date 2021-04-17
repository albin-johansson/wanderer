#pragma once

#include <step_map.hpp>

#include "core/aliases/texture_id.hpp"
#include "core/aliases/tile_id.hpp"
#include "io/map/parse_ir.hpp"

namespace wanderer {

[[nodiscard]] auto make_tile(tile_id id,
                             int index,
                             texture_id texture,
                             const step::tileset& tileset) -> ir::tile;

[[nodiscard]] auto parse_fancy_tile(ir::tileset& data,
                                    const ir::tile& tileData,
                                    const step::tile& tile,
                                    tile_id firstGid) -> ir::fancy_tile;

}  // namespace wanderer