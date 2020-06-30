#pragma once

#include <renderer.h>

#include "tile.h"
#include "tileset.h"

namespace wanderer::system::tile {

void render(ctn::Renderer& renderer,
            const Tile& tile,
            int row,
            int col) noexcept;

[[nodiscard]] auto animated_tile(entt::registry& registry,
                                 const TileEntity tileEntity,
                                 const Tileset& tileset) -> const Tile&;

}  // namespace wanderer::system::tile
