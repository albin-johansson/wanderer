#pragma once

#include <renderer.h>

#include "tile.h"
#include "tileset.h"

namespace wanderer::system::tile {

void render(ctn::Renderer& renderer,
            const component::Tile& tile,
            int row,
            int col) noexcept;

[[nodiscard]] auto animated_tile(entt::registry& registry,
                                 const component::Tile::entity tileEntity,
                                 const component::Tileset& tileset)
    -> const component::Tile&;

}  // namespace wanderer::system::tile
