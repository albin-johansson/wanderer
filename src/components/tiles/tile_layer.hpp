#pragma once

#include <vector>  // vector

#include "common/entity_type.hpp"
#include "common/ints.hpp"
#include "common/tile_id.hpp"

namespace wanderer::comp {

/**
 * \struct tile_layer
 *
 * \brief Represents a layer of tiles.
 *
 * \details Multiple tile layers are combined to create tilemaps.
 *
 * \headerfile tile_layer.hpp
 */
struct tile_layer final
{
  using tile_matrix = std::vector<std::vector<tile_id>>;

  tile_matrix matrix;  ///< Matrix of tile IDs that represent the layer.
  int32 z{};           ///< Index that indicates when the layer should be rendered.
};

}  // namespace wanderer::comp
