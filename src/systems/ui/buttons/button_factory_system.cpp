#include <utility>  // move

#include "button_system.hpp"

namespace wanderer::sys {

void add_button(entt::registry& registry,
                const entt::entity entity,
                std::string text,
                const menu_action action,
                const int row,
                const int col)
{
  auto& button = registry.emplace<comp::button>(entity);
  button.text = std::move(text);
  button.action = action;
  button.row = row;
  button.col = col;
  button.hover = false;

  registry.emplace<comp::button_drawable>(entity);
}

auto make_button(entt::registry& registry,
                 std::string text,
                 const menu_action action,
                 const int row,
                 const int col) -> comp::button::entity
{
  const auto entity = comp::button::entity{registry.create()};

  add_button(registry, entity, std::move(text), action, row, col);

  return entity;
}

}  // namespace wanderer::sys
