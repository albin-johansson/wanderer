#ifndef RUNE_ECS_UI_UI_GRID_HPP
#define RUNE_ECS_UI_UI_GRID_HPP

#include <centurion.hpp>  // fpoint

#include "../../core/configuration.hpp"
#include "ui_position.hpp"

namespace rune::ui {

/// \addtogroup ecs
/// \{

/// \name Grid functions
/// \{

[[nodiscard]] inline auto row_to_y(const float row) -> float
{
  return row * get_ui_row_size();
}

[[nodiscard]] inline auto column_to_x(const float column) -> float
{
  return column * get_ui_column_size();
}

[[nodiscard]] inline auto from_grid(const float row, const float column) -> cen::fpoint
{
  return {column_to_x(column), row_to_y(row)};
}

[[nodiscard]] inline auto from_grid(const ui_position position) -> cen::fpoint
{
  return {column_to_x(position.col), row_to_y(position.row)};
}

/// \} End of grid functions

/// \} End of group ecs

}  // namespace rune::ui

#endif  // RUNE_ECS_UI_UI_GRID_HPP
