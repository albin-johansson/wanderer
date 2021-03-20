#pragma once

#include "menu_constants.hpp"

namespace wanderer::sys {

[[nodiscard]] constexpr auto convert_column_to_x(const int column) -> int
{
  // make centered if column index is -1
  if (column == -1)
  {
    return (glob::logical_width<int> / 2);
  }
  else
  {
    return (column * glob::menu_col_size);
  }
}

[[nodiscard]] constexpr auto convert_row_to_y(const int row) -> int
{
  return (row * glob::menu_col_size);
}

}  // namespace wanderer::sys
