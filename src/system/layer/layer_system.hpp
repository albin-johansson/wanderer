#pragma once

#include "render_bounds.hpp"
#include "tile_layer.hpp"

namespace wanderer::sys::layer {

/**
 * \brief Visits all tiles in a tile layer.
 *
 * \details Empty tiles will be ignored by this function. The signature of
 * the function object should be equivalent to `void(tile_id)`.
 *
 * \tparam T the type of the function object.
 *
 * \param layer the layer whose tiles will be visited.
 * \param callable the function object that will be invoked for each tile.
 *
 * \since 0.1.0
 */
template <typename T>
void visit(const comp::tile_layer& layer, T&& callable)
{
  const auto rows = layer.matrix.size();
  const auto cols = layer.matrix.at(0).size();

  for (auto r = 0; r < rows; ++r) {
    for (auto c = 0; c < cols; ++c) {
      const auto tileId = layer.matrix.at(r).at(c);
      if (!is_empty(tileId)) {
        callable(tileId);
      }
    }
  }
}

/**
 * \brief Visits all tiles in a tile layer that are within the specified bounds.
 *
 * \details Empty tiles will be ignored by this function. The signature of
 * the function object should be equivalent to `void(tile_id, int, int)`,
 * where the two integers are the row and column indices, respectively.
 *
 * \tparam T the type of the function object.
 *
 * \param layer the layer whose tiles will be visited.
 * \param bounds the bounds that the visited tiles must be within.
 * \param callable the function object that will be invoked for each tile
 * within the bounds.
 *
 * \since 0.1.0
 */
template <typename T>
void visit(const comp::tile_layer& layer,
           const comp::render_bounds& bounds,
           T&& callable)
{
  for (auto r = bounds.minRow; r < bounds.maxRow; ++r) {
    for (auto c = bounds.minCol; c < bounds.maxCol; ++c) {
      const auto tileId = layer.matrix.at(r).at(c);
      if (!is_empty(tileId)) {
        callable(tileId, r, c);
      }
    }
  }
}

}  // namespace wanderer::sys::layer
