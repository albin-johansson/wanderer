#pragma once

#include <rune.hpp>  // tmx_tile_layer

#include "components/tile_layer.hpp"

namespace wanderer::io {

[[nodiscard]] auto parse_ground_layer(const rune::tmx_tile_layer& tileLayer,
                                      int nRows,
                                      int nCols,
                                      int layerIndex) -> comp::tile_layer;

}  // namespace wanderer::io
