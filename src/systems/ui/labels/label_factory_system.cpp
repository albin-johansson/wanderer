#include "label_factory_system.hpp"

#include <utility>  // move

#include <centurion.hpp>  // colors

#include "components/ui/associated_menu.hpp"

namespace wanderer::sys {

auto MakeLabel(entt::registry& registry,
               const entt::entity menu,
               std::string text,
               const GridPosition position,
               const TextSize size) -> entt::entity
{
  const auto entity = registry.create();

  auto& label = registry.emplace<comp::Label>(entity);
  label.text = std::move(text);
  label.position = position;
  label.color = cen::colors::white;
  label.size = size;

  auto& associated = registry.emplace<comp::AssociatedMenu>(entity);
  associated.entity = menu;

  return entity;
}

}  // namespace wanderer::sys
