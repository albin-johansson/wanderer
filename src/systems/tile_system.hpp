#pragma once

#include <entt.hpp>  // registry

#include "components/tile.hpp"
#include "wanderer_std.hpp"

namespace wanderer::sys {

[[nodiscard]] auto GetTile(entt::registry& registry, TileID id) -> Tile&;

}  // namespace wanderer::sys
