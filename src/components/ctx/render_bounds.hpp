#pragma once

#include "common/ints.hpp"

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
  uint64 min_row{};  ///< The minimum row index of tiles that will be rendered.
  uint64 min_col{};  ///< The minimum column index of tiles that will be rendered.
  uint64 max_row{};  ///< The maximum row index of tiles that will be rendered.
  uint64 max_col{};  ///< The maximum column index of tiles that will be rendered.
};

void serialize(auto& archive, render_bounds& rb, uint32 version)
{
  archive(rb.min_row, rb.min_col, rb.max_row, rb.max_col);
}

}  // namespace wanderer::ctx
