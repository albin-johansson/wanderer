#pragma once

#include "ints.hpp"

namespace wanderer::comp {

/**
 * \struct render_bounds
 *
 * \brief Represents the bounds of a map that will be rendered.
 *
 * \var render_bounds::minRow
 * The minimum row index in the tile layers that will be rendered.
 * \var render_bounds::minCol
 * The minimum column index in the tile layers that will be rendered.
 * \var render_bounds::maxRow
 * The maximum row index in the tile layers that will be rendered.
 * \var render_bounds::maxCol
 * The maximum column index in the tile layers that will be rendered.
 *
 * \headerfile render_bounds.hpp
 */
struct render_bounds final
{
  int minRow{};
  int minCol{};
  int maxRow{};
  int maxCol{};
};

template <typename Archive>
void serialization(Archive& archive, render_bounds& rb, u32 version)
{
  archive(rb.minRow, rb.minCol, rb.maxRow, rb.maxCol);
}

}  // namespace wanderer::comp
