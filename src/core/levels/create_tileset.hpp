#pragma once

#include <entt.hpp>  // registry

#include "core/graphics_context.hpp"
#include "ctx/tileset.hpp"
#include "io/map/parse_ir.hpp"

namespace wanderer {

void load_tileset_textures(const ir::level& data, graphics_context& graphics);

[[nodiscard]] auto create_tileset(const std::vector<ir::tileset>& data,
                                  entt::registry& registry,
                                  const graphics_context& graphics) -> ctx::tileset&;

}  // namespace wanderer
