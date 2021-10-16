#pragma once

#include "common/ints.hpp"

namespace wanderer::ctx {

struct LevelSize final
{
  uint64 row_count{};  ///< The number of rows in the level.
  uint64 col_count{};  ///< The number of columns in the level.
};

}  // namespace wanderer::ctx
