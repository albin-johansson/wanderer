#pragma once

#include <renderer.h>

#include "tile.h"
#include "tileset.h"

namespace wanderer::system::tile {

void render(centurion::Renderer& renderer,
            const Tile& tile,
            int row,
            int col) noexcept;

auto animated_tile(entt::registry& registry,
                   const entt::entity tileEntity,
                   const Tileset& tileset) -> const Tile&;

}  // namespace wanderer::system::tile
