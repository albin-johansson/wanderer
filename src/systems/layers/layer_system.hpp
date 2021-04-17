#pragma once

#include <concepts>  // invocable
#include <entt.hpp>  // registry

#include "components/map/tile_layer.hpp"
#include "core/graphics_context.hpp"
#include "ctx/render_bounds.hpp"

namespace wanderer::sys {

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

/**
 * \brief Visits all tiles in a tile layer.
 *
 * \details Empty tiles will be ignored by this function.
 *
 * \tparam T the type of the function object.
 *
 * \param layer the layer whose tiles will be visited.
 * \param callable the function object that will be invoked for each tile.
 *
 * \since 0.1.0
 */
template <std::invocable<tile_id, int, int> T>
void visit_tiles(const comp::tile_layer& layer, T&& callable)
{
  ctx::render_bounds bounds;
  bounds.minRow = 0;
  bounds.minCol = 0;
  bounds.maxRow = layer.matrix.size();
  bounds.maxCol = layer.matrix.at(0).size();
  visit_tiles(layer, bounds, callable);
}

/**
 * \brief Renders all of the ground layers in a map.
 *
 * \param registry the registry that holds the layers.
 * \param graphics the graphics context that will be used when rendering.
 *
 * \since 0.1.0
 */
void render_ground_layers(const entt::registry& registry, graphics_context& graphics);

}  // namespace wanderer::sys
