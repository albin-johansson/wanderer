#pragma once

namespace wanderer::ctx {

struct level_size final
{
  int row_count{};  ///< The number of rows in the level.
  int col_count{};  ///< The number of columns in the level.
};

}  // namespace wanderer::ctx
