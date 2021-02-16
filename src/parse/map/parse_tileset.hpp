#pragma once

#include <step_map.hpp>

#include "graphics_context.hpp"
#include "parse_ir.hpp"

namespace wanderer {

using tileset_collection = std::vector<std::unique_ptr<step::tileset>>;

[[nodiscard]] auto parse_tileset(const tileset_collection& tilesets,
                                 graphics_context& graphics) -> ir::tileset;

}  // namespace wanderer
