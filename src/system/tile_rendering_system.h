#pragma once

#include <renderer.h>

#include "tile.h"

namespace wanderer::system::tile {

void render(centurion::Renderer& renderer,
            const Tile& tile,
            int row,
            int col) noexcept;

}  // namespace wanderer::system::tile
