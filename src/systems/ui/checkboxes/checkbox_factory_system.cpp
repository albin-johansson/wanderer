#include "checkbox_factory_system.hpp"

#include <utility>  // move

#include "button_factory_system.hpp"

namespace wanderer::sys {

auto add_checkbox(entt::registry& registry,
                  std::string text,
                  const int row,
                  const int col,
                  const menu_action action,
                  const bool checked) -> comp::checkbox::entity
{
  const auto entity = comp::checkbox::entity{registry.create()};

  add_button(registry, entity, std::move(text), row, col, action);

  auto& checkbox = registry.emplace<comp::checkbox>(entity);
  checkbox.checked = checked;

  return entity;
}

}  // namespace wanderer::sys
