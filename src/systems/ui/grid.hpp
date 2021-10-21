#pragma once

#include <centurion.hpp>  // fpoint

#include "core/game_constants.hpp"
#include "core/grid_position.hpp"

namespace wanderer::sys {

/// \name UI
/// \{

[[nodiscard]] constexpr auto ColumnToX(const float column) noexcept -> float
{
  // make centered if column index is -1
  if (column == -1) {
    return (glob::logical_width<float> / 2.0f);
  }
  else {
    return (column * glob::menu_col_size);
  }
}

[[nodiscard]] constexpr auto RowToY(const float row) noexcept -> float
{
  return (row * glob::menu_col_size);
}

[[nodiscard]] constexpr auto FromGrid(const float row, const float column) noexcept
    -> cen::fpoint
{
  return {ColumnToX(column), RowToY(row)};
}

[[nodiscard]] constexpr auto FromGrid(const GridPosition position) noexcept -> cen::fpoint
{
  return {ColumnToX(position.col), RowToY(position.row)};
}

template <typename T>
[[nodiscard]] constexpr auto CenterX(const T width) noexcept -> T
{
  return (glob::logical_width<T> - width) / T{2};
}

/// \} End of UI

}  // namespace wanderer::sys
