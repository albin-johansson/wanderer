#pragma once

#include <entt.hpp>  // registry

#include "components/map/tile.hpp"
#include "core/aliases/tile_id.hpp"

namespace wanderer::sys {

[[nodiscard]] auto get_tile(entt::registry& registry, tile_id id) -> comp::tile&;

}  // namespace wanderer::sys
