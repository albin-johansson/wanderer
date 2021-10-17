#pragma once

#include <entt.hpp>  // registry

#include "common/tile_id.hpp"
#include "components/tiles/tile.hpp"

namespace wanderer::sys {

[[nodiscard]] auto GetTile(entt::registry& registry, tile_id id) -> comp::Tile&;

}  // namespace wanderer::sys
