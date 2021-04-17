#pragma once

#include <concepts>  // invocable
#include <entt.hpp>  // registry

#include "components/ctx/render_bounds.hpp"
#include "components/map/tile_layer.hpp"
#include "core/graphics/graphics_context.hpp"

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
 * \tparam T the type of the function object.
 *
 * \param layer the layer whose tiles will be visited.
 * \param bounds the bounds that the visited tiles must be within.
 * \param callable the function object that will be invoked for each tile
 * within the bounds.
 *
 * \since 0.1.0
 */
template <std::invocable<tile_id, int, int> T>
void visit_tiles(const comp::tile_layer& layer,
                 const ctx::render_bounds& bounds,
                 T&& callable)
{
  for (auto row = bounds.minRow; row < bounds.maxRow; ++row)
  {
    for (auto col = bounds.minCol; col < bounds.maxCol; ++col)
    {
      const auto id = layer.matrix.at(row).at(col);
      if (!is_empty(id))
      {
        callable(id, row, col);
      }
    }
  }
}

/// \} End of tile layers

}  // namespace wanderer::sys