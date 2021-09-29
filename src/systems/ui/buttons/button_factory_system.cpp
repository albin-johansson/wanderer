#include "button_factory_system.hpp"

#include <utility>  // move

namespace wanderer::sys {

void add_button(entt::registry& registry,
                const entt::entity entity,
                std::string text,
                const menu_action action,
                const grid_position position)
{
  auto& button = registry.emplace<comp::button>(entity);
  button.text = std::move(text);
  button.action = action;
  button.position = position;

  registry.emplace<comp::button_drawable>(entity);
}

auto make_button(entt::registry& registry,
                 std::string text,
                 const menu_action action,
                 const grid_position position) -> entt::entity
{
  const auto entity = registry.create();

  add_button(registry, entity, std::move(text), action, position);

  return entity;
}

}  // namespace wanderer::sys
