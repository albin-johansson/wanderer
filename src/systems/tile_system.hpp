#pragma once

#include <entt.hpp>  // registry

#include "common/tile_id.hpp"
#include "components/tiles/tile.hpp"

namespace wanderer::sys {

[[nodiscard]] auto get_tile(entt::registry& registry, tile_id id) -> comp::tile&;

}  // namespace wanderer::sys