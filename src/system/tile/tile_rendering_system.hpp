#pragma once

#include <cen/renderer.hpp>

#include "component/tile.hpp"
#include "component/tileset.hpp"

namespace wanderer::sys::tile {

void render(cen::renderer& renderer,
            const comp::tile& tile,
            int row,
            int col) noexcept;

[[nodiscard]] auto animated_tile(entt::registry& registry,
                                 const comp::tile::entity tileEntity,
                                 const comp::tileset& tileset)
    -> const comp::tile&;

}  // namespace wanderer::sys::tile
