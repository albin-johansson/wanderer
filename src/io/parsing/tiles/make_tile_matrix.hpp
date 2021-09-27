#pragma once

#include "components/tiles/tile_layer.hpp"

namespace wanderer::io {

[[nodiscard]] auto make_tile_matrix(int nRows, int nCols)
    -> comp::tile_layer::tile_matrix;

}  // namespace wanderer::io
