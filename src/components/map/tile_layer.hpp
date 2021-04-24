#pragma once

#include <vector>  // vector

#include "core/aliases/entity_type.hpp"
#include "core/aliases/ints.hpp"
#include "core/aliases/tile_id.hpp"

namespace wanderer::comp {
namespace detail {
struct tile_layer_entity_t;
}

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
  using entity = entity_type<detail::tile_layer_entity_t>;
  using tile_matrix = std::vector<std::vector<tile_id>>;

  tile_matrix matrix;  ///< Matrix of tile IDs that represent the layer.
  int z;               ///< Index that indicates when the layer should be rendered.
};

void serialize(auto& archive, tile_layer& layer, u32 version)
{
  archive(layer.matrix, layer.z);
}

}  // namespace wanderer::comp
