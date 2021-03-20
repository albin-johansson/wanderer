#include "button_factory_system.hpp"

#include <utility>  // move

#include "create_action.hpp"

namespace wanderer::sys {

void add_button(entt::registry& registry,
                const entt::entity entity,
                std::string text,
                const int row,
                const int col,
                const menu_action action)
{
  auto& button = registry.emplace<comp::button>(entity);
  button.text = std::move(text);
  button.row = row;
  button.col = col;
  button.action = create_action(action);
  button.hover = false;

  registry.emplace<comp::button_drawable>(entity);
}

auto make_button(entt::registry& registry,
                 std::string text,
                 const int row,
                 const int col,
                 const menu_action action) -> comp::button::entity
{
  const auto entity = comp::button::entity{registry.create()};

  add_button(registry, entity, std::move(text), row, col, action);

  return entity;
}

}  // namespace wanderer::sys
