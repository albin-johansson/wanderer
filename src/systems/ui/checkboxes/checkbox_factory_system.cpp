#include "checkbox_factory_system.hpp"

#include <utility>  // move

#include "systems/ui/buttons/button_factory_system.hpp"
#include "systems/ui/grid.hpp"

namespace wanderer::sys {

auto make_checkbox(entt::registry& registry,
                   std::string text,
                   const GridPosition position,
                   const MenuAction action,
                   const bool checked) -> entt::entity
{
  const auto entity = registry.create();

  add_button(registry, entity, std::move(text), action, position);

  const auto& button = registry.get<comp::Button>(entity);

  const auto pos = from_grid(button.position);
  const cen::frect rect{pos.x(), pos.y(), 10, 10};

  auto& drawable = registry.get<comp::ButtonDrawable>(entity);
  drawable.bounds = cen::cast<cen::frect>(rect);
  drawable.text_pos = drawable.bounds.position();
  drawable.text_pos->set_x(drawable.text_pos->x() + 14);
  drawable.text_pos->set_y(drawable.text_pos->y() - 2);

  auto& checkbox = registry.emplace<comp::Checkbox>(entity);
  checkbox.checked = checked;

  return entity;
}

}  // namespace wanderer::sys
