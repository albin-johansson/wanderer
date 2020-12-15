#pragma once

#include <entt.hpp>      // registry
#include <step_map.hpp>  // tile_layer, properties

#include "tilemap.hpp"

namespace wanderer {

/**
 * \brief Parses a tile layer.
 *
 * \param registry the associated registry.
 * \param tilemap the tilemap component associated with the layer.
 * \param layer the tile layer representation.
 * \param properties the properties associated with the layer.
 * \param index the index associated with the layer.
 *
 * \since 0.1.0
 */
void parse_tile_layer(entt::registry& registry,
                      comp::tilemap& tilemap,
                      const step::tile_layer& layer,
                      const step::properties* properties,
                      int index);

}  // namespace wanderer
