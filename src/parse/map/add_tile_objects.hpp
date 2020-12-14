#pragma once

#include <entt.hpp>
#include <step_data.hpp>

#include "map_position.hpp"
#include "tilemap.hpp"
#include "tileset.hpp"

namespace wanderer {

using tile_data = step::detail::data::gid_data;  // FIXME

void add_tile_objects(entt::registry& registry,
                      comp::tilemap& tilemap,
                      const comp::tileset& tileset,
                      const tile_data& data,
                      int layerIndex);

}  // namespace wanderer
