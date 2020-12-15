#pragma once

#include <entt.hpp>
#include <step_map.hpp>

#include "tilemap.hpp"

namespace wanderer {

void parse_tile_layer(entt::registry& registry,
                      comp::tilemap& tilemap,
                      const step::tile_layer& layer,
                      const step::properties* properties,
                      int index);

}  // namespace wanderer
