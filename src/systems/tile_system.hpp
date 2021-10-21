#pragma once

#include <entt.hpp>  // registry

#include "components/tiles/tile.hpp"
#include "wanderer_std.hpp"

namespace wanderer::sys {

[[nodiscard]] auto GetTile(entt::registry& registry, tile_id id) -> comp::Tile&;

}  // namespace wanderer::sys
