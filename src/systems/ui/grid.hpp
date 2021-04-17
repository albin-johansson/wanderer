#pragma once

#include <centurion.hpp>  // fpoint

#include "core/menu_constants.hpp"

namespace wanderer::sys {

/// \name UI
/// \{

[[nodiscard]] constexpr auto column_to_x(const float column) -> float
{
  // make centered if column index is -1
  if (column == -1)
  {
    return (glob::logical_width<float> / 2.0f);
  }
  else
  {
    return (column * glob::menu_col_size);
  }
}

[[nodiscard]] constexpr auto row_to_y(const float row) -> float
{
  return (row * glob::menu_col_size);
}

[[nodiscard]] constexpr auto from_grid(const float row, const float column) -> cen::fpoint
{
  return {column_to_x(column), row_to_y(row)};
}

/// \} End of UI

}  // namespace wanderer::sys
