#include "button_factory_system.hpp"

#include <utility>  // move

namespace wanderer::sys {

void AddButton(entt::registry& registry,
               const entt::entity entity,
               std::string text,
               const MenuAction action,
               const GridPosition position)
{
  auto& button = registry.emplace<comp::Button>(entity);
  button.text = std::move(text);
  button.action = action;
  button.position = position;

  registry.emplace<comp::ButtonDrawable>(entity);
}

auto MakeButton(entt::registry& registry,
                std::string text,
                const MenuAction action,
                const GridPosition position) -> entt::entity
{
  const auto entity = registry.create();

  AddButton(registry, entity, std::move(text), action, position);

  return entity;
}

}  // namespace wanderer::sys
