#pragma once

#include "component/render_bounds.hpp"
#include "component/tile_layer.hpp"

namespace wanderer::sys::layer {

template <typename T>
void visit(const comp::tile_layer& layer, T&& callable)
{
  const auto rows = layer.matrix.size();
  const auto cols = layer.matrix.at(0).size();

  for (auto r = 0; r < rows; ++r) {
    for (auto c = 0; c < cols; ++c) {
      const auto tileId = layer.matrix.at(r).at(c);
      if (tileId != g_emptyTile) {
        callable(tileId);
      }
    }
  }
}

template <typename T>
void visit(const comp::tile_layer& layer,
           const comp::render_bounds& bounds,
           T&& callable)
{
  for (auto r = bounds.minRow; r < bounds.maxRow; ++r) {
    for (auto c = bounds.minCol; c < bounds.maxCol; ++c) {
      const auto tileId = layer.matrix.at(r).at(c);
      if (tileId != g_emptyTile) {
        callable(tileId, r, c);
      }
    }
  }
}

}  // namespace wanderer::sys::layer
