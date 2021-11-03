#include "checkbox_factory_system.hpp"

#include <utility>  // move

#include "components/ui/associated_menu.hpp"
#include "systems/ui/buttons/button_factory_system.hpp"
#include "systems/ui/grid.hpp"

namespace wanderer::sys {

auto MakeCheckbox(entt::registry& registry,
                  std::string text,
                  const GridPosition position,
                  const Action action,
                  const bool checked) -> entt::entity
{
  const auto entity = registry.create();

  AddButton(registry, entity, std::move(text), action, position);

  const auto& button = registry.get<Button>(entity);

  const auto pos = FromGrid(button.position);
  const cen::frect rect{pos.x(), pos.y(), 10, 10};

  auto& drawable = registry.get<ButtonDrawable>(entity);
  drawable.bounds = cen::cast<cen::frect>(rect);
  drawable.text_pos = drawable.bounds.position();
  drawable.text_pos->set_x(drawable.text_pos->x() + 14);
  drawable.text_pos->set_y(drawable.text_pos->y() - 2);

  auto& checkbox = registry.emplace<Checkbox>(entity);
  checkbox.checked = checked;

  return entity;
}

auto MakeCheckbox(entt::registry& registry,
                  const entt::entity menuEntity,
                  std::string text,
                  const Action action,
                  const GridPosition position,
                  const bool checked) -> entt::entity
{
  const auto entity = MakeCheckbox(registry, std::move(text), position, action, checked);

  auto& associated = registry.emplace<AssociatedMenu>(entity);
  associated.entity = menuEntity;

  return entity;
}

}  // namespace wanderer::sys
