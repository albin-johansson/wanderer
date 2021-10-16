#pragma once

#include "components/tiles/tile_layer.hpp"

namespace wanderer::io {

[[nodiscard]] auto make_tile_matrix(int nRows, int nCols) -> comp::TileLayer::tile_matrix;

}  // namespace wanderer::io
