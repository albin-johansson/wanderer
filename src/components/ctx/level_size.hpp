#pragma once

namespace wanderer::ctx {

struct level_size final
{
  int rows{};  ///< The number of rows in the level.
  int cols{};  ///< The number of columns in the level.
};

}  // namespace wanderer::ctx
