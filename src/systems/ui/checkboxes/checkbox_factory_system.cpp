#include "checkbox_factory_system.hpp"

#include <utility>  // move

#include "systems/ui/buttons/button_factory_system.hpp"
#include "systems/ui/grid.hpp"

namespace wanderer::sys {

auto make_checkbox(entt::registry& registry,
                   std::string text,
                   const grid_position position,
                   const menu_action action,
                   const bool checked) -> comp::checkbox::entity
{
  const auto entity = comp::checkbox::entity{registry.create()};

  add_button(registry, entity, std::move(text), action, position);

  const auto& button = registry.get<comp::button>(entity);

  const auto pos = from_grid(button.position);
  const cen::frect rect{pos.x(), pos.y(), 10, 10};

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
