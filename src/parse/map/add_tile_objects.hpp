#pragma once

#include <entt.hpp>
#include <step_data.hpp>

#include "map_position.hpp"
#include "tilemap.hpp"
#include "tileset.hpp"

namespace wanderer {

using tile_iterator = step::detail::data::gid_data::const_iterator;

void add_tile_objects(entt::registry& registry,
                      comp::tilemap& tilemap,
                      const comp::tileset& tileset,
                      tile_iterator&& begin,
                      tile_iterator&& end);

}  // namespace wanderer
