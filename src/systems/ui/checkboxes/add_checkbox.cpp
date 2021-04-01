#include "checkbox_system.hpp"

#include <utility>  // move

#include "button_system.hpp"
#include "grid_system.hpp"

namespace wanderer::sys {

auto add_checkbox(entt::registry& registry,
                  std::string text,
                  const int row,
                  const int col,
                  const menu_action action,
                  const bool checked) -> comp::checkbox::entity
{
  const auto entity = comp::checkbox::entity{registry.create()};

  add_button(registry, entity, std::move(text), action, row, col);

  const auto& button = registry.get<comp::button>(entity);

  const auto x = convert_column_to_x(button.col);
  const auto y = convert_row_to_y(button.row);
  const cen::irect rect{x, y, 10, 10};

  auto& drawable = registry.get<comp::button_drawable>(entity);
  drawable.bounds = cen::cast<cen::frect>(rect);
  drawable.textPos = drawable.bounds.position();
  drawable.textPos->set_x(drawable.textPos->x() + 14);
  drawable.textPos->set_y(drawable.textPos->y() - 2);

  auto& checkbox = registry.emplace<comp::checkbox>(entity);
  checkbox.checked = checked;

  return entity;
}

}  // namespace wanderer::sys
