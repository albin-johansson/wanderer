#pragma once

#include <vector>  // vector

#include "common/ints.hpp"
#include "common/tile_id.hpp"

namespace wanderer::comp {

/// \brief Represents a layer of tiles.
/// \ingroup components
struct TileLayer final
{
  using tile_matrix = std::vector<std::vector<tile_id>>;

  tile_matrix matrix;  ///< Matrix of tile IDs that represent the layer.
  int32 z{};           ///< Index that indicates when the layer should be rendered.
};

}  // namespace wanderer::comp
