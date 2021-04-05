#pragma once

#include <centurion.hpp>

#include "graphics_context.hpp"
#include "tile.hpp"
#include "tileset.hpp"

namespace wanderer::sys {

void render_tile(graphics_context& graphics,
                 const comp::tile& tile,
                 int row,
                 int col) noexcept;

[[nodiscard]] auto get_animated_tile(const entt::registry& registry,
                                     comp::tile::entity tileEntity,
                                     const ctx::tileset& tileset) -> const comp::tile&;

}  // namespace wanderer::sys
