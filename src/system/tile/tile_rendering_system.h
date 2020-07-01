#pragma once

#include <renderer.h>

#include "tile.h"
#include "tileset.h"

namespace wanderer::system::tile {

void render(ctn::Renderer& renderer,
            const comp::Tile& tile,
            int row,
            int col) noexcept;

[[nodiscard]] auto animated_tile(entt::registry& registry,
                                 const comp::Tile::entity tileEntity,
                                 const comp::Tileset& tileset)
    -> const comp::Tile&;

}  // namespace wanderer::system::tile
