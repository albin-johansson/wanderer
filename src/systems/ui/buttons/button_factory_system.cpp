#include "button_factory_system.hpp"

#include <utility>  // move

#include "components/ui/associated_menu.hpp"

namespace wanderer::sys {

void AddButton(entt::registry& registry,
               const entt::entity entity,
               std::string text,
               const Action action,
               const GridPosition position)
{
  auto& button = registry.emplace<Button>(entity);
  button.text = std::move(text);
  button.action = action;
  button.position = position;

  registry.emplace<ButtonDrawable>(entity);
}

auto MakeButton(entt::registry& registry,
                std::string text,
                const Action action,
                const GridPosition position) -> entt::entity
{
  const auto entity = registry.create();

  AddButton(registry, entity, std::move(text), action, position);

  return entity;
}

auto MakeButton(entt::registry& registry,
                const entt::entity menuEntity,
                std::string text,
                const Action action,
                const GridPosition position) -> entt::entity
{
  const auto entity = registry.create();

  AddButton(registry, entity, std::move(text), action, position);

  auto& associated = registry.emplace<AssociatedMenu>(entity);
  associated.entity = menuEntity;

  return entity;
}

}  // namespace wanderer::sys
