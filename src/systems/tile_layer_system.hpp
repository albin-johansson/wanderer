#pragma once

#include <cassert>   // assert
#include <concepts>  // invocable
#include <entt.hpp>  // registry

#include "components/ctx/render_bounds.hpp"
#include "components/map/tile_layer.hpp"
#include "core/graphics/graphics_context.hpp"
#include "core/grid_position.hpp"

namespace wanderer::sys {

/// \name Tile layers
/// \{

/**
 * \brief Visits all tiles in a tile layer that are within the specified bounds.
 *
 * \details Empty tiles will be ignored by this function. The signature of
 * the function object features two integers, that correspond to the row and column
 * indices, respectively.
 *
 * \ingroup systems
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
template <std::invocable<tile_id, grid_position> T>
void visit_tiles(const comp::tile_layer& layer,
                 const ctx::render_bounds& bounds,
                 T&& callable)
{
  for (auto row = bounds.min_row; row < bounds.max_row; ++row)
  {
    for (auto col = bounds.min_col; col < bounds.max_col; ++col)
    {
      assert(row >= 0);
      assert(row < layer.matrix.size());
      assert(col >= 0);
      assert(col < layer.matrix.at(row).size());

      const auto id = layer.matrix[row][col];
      if (!is_empty(id))
      {
        callable(id, grid_position{static_cast<float>(row), static_cast<float>(col)});
      }
    }
  }
}

/// \} End of tile layers

}  // namespace wanderer::sys
