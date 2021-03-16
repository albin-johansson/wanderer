#pragma once

#include <entt.hpp>

#include "graphics_context.hpp"
#include "parse_ir.hpp"
#include "tileset.hpp"

namespace wanderer {

void load_tileset_textures(const ir::level& data, graphics_context& graphics);

[[nodiscard]] auto create_tileset(const std::vector<ir::tileset>& data,
                                  entt::registry& registry,
                                  comp::tileset::entity entity)
    -> comp::tileset&;

}  // namespace wanderer
