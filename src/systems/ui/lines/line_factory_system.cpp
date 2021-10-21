#include "line_factory_system.hpp"

#include "components/ui/associated_menu.hpp"

namespace wanderer::sys {

auto MakeLine(entt::registry& registry, const GridPosition start, const GridPosition end)
    -> entt::entity
{
  const auto entity = registry.create();

  auto& line = registry.emplace<comp::Line>(entity);
  line.start = start;
  line.end = end;

  return entity;
}

auto MakeLine(entt::registry& registry,
              const entt::entity menuEntity,
              const GridPosition start,
              const GridPosition end) -> entt::entity
{
  const auto entity = MakeLine(registry, start, end);

  auto& associated = registry.emplace<comp::AssociatedMenu>(entity);
  associated.entity = menuEntity;

  return entity;
}

}  // namespace wanderer::sys
