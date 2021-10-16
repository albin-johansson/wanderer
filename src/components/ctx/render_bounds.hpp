#pragma once

#include "common/ints.hpp"

namespace wanderer::ctx {

/// \brief Represents the bounds of a map that will be rendered.
struct RenderBounds final
{
  uint64 min_row{};  ///< The minimum row index of tiles that will be rendered.
  uint64 min_col{};  ///< The minimum column index of tiles that will be rendered.
  uint64 max_row{};  ///< The maximum row index of tiles that will be rendered.
  uint64 max_col{};  ///< The maximum column index of tiles that will be rendered.
};

}  // namespace wanderer::ctx
