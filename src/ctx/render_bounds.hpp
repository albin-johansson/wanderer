#pragma once

#include "core/aliases/ints.hpp"

namespace wanderer::ctx {

/**
 * \struct render_bounds
 *
 * \brief Represents the bounds of a map that will be rendered.
 *
 * \headerfile render_bounds.hpp
 */
struct render_bounds final
{
  int minRow{};  ///< The minimum row index of tiles that will be rendered.
  int minCol{};  ///< The minimum column index of tiles that will be rendered.
  int maxRow{};  ///< The maximum row index of tiles that will be rendered.
  int maxCol{};  ///< The maximum column index of tiles that will be rendered.
};

void serialize(auto& archive, render_bounds& rb, u32 version)
{
  archive(rb.minRow, rb.minCol, rb.maxRow, rb.maxCol);
}

}  // namespace wanderer::ctx
