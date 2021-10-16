#include "line_factory_system.hpp"

namespace wanderer::sys {

auto make_line(entt::registry& registry,
               const grid_position start,
               const grid_position end) -> entt::entity
{
  const auto entity = registry.create();

  auto& line = registry.emplace<comp::Line>(entity);
  line.start = start;
  line.end = end;

  return entity;
}

}  // namespace wanderer::sys
