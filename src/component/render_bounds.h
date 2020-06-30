/**
 * @brief Provides the `RenderBounds` component.
 * @file render_bounds.h
 * @author Albin Johansson
 * @copyright MIT License
 * @date 2020
 */

#pragma once

namespace wanderer {

/**
 * @struct RenderBounds
 * @brief Represents the bounds of a map that will be rendered.
 *
 * @var RenderBounds::minRow
 * The minimum row index in the tile layers that will be rendered.
 * @var RenderBounds::minCol
 * The minimum column index in the tile layers that will be rendered.
 * @var RenderBounds::maxRow
 * The maximum row index in the tile layers that will be rendered.
 * @var RenderBounds::maxCol
 * The maximum column index in the tile layers that will be rendered.
 *
 * @headerfile render_bounds.h
 */
struct RenderBounds final {
  int minRow{};
  int minCol{};
  int maxRow{};
  int maxCol{};
};

}  // namespace wanderer
