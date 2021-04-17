#pragma once

#include "components/map/tile.hpp"
#include "core/graphics_context.hpp"
#include "ctx/tileset.hpp"

namespace wanderer::sys {

// TODO make row and col floats
void render_tile(graphics_context& graphics,
                 const comp::tile& tile,
                 int row,
                 int col) noexcept;

[[nodiscard]] auto get_animated_tile(const entt::registry& registry,
                                     comp::tile::entity tileEntity,
                                     const ctx::tileset& tileset) -> const comp::tile&;

}  // namespace wanderer::sys
