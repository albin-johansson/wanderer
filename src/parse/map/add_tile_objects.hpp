#pragma once

#include <entt.hpp>       // registry
#include <step_data.hpp>  // data::gid_data

#include "tileset.hpp"

namespace wanderer {

using tile_data = step::detail::data::gid_data;  // FIXME

/**
 * \brief Adds tile objects to a map.
 *
 * \details Tile objects are entities that feature depth heuristics and
 * optionally hitboxes.
 *
 * \param registry the associated registry.
 * \param tileset the associated tileset component.
 * \param data the tile data of the tilemap representation.
 * \param nColumns the number of columns in the associated tilemap. Used to
 * calculate row/col indices.
 * \param layerIndex the index of the associated layer.
 *
 * \since 0.1.0
 */
void add_tile_objects(entt::registry& registry,
                      const comp::tileset& tileset,
                      const tile_data& data,
                      int nColumns,
                      int layerIndex);

}  // namespace wanderer
