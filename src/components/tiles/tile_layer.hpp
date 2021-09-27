#pragma once

#include <vector>  // vector

#include "common/entity_type.hpp"
#include "common/ints.hpp"
#include "common/tile_id.hpp"

namespace wanderer::comp {

namespace tags {
struct tile_layer_tag;
}  // namespace tags

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
  using entity = entity_type<tags::tile_layer_tag>;
  using tile_matrix = std::vector<std::vector<tile_id>>;

  tile_matrix matrix;  ///< Matrix of tile IDs that represent the layer.
  int z{};             ///< Index that indicates when the layer should be rendered.
};

void serialize(auto& archive, tile_layer& layer, uint32 version)
{
  archive(layer.matrix, layer.z);
}

}  // namespace wanderer::comp
