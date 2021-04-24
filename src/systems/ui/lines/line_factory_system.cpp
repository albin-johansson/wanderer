#include "line_factory_system.hpp"

namespace wanderer::sys {

auto make_line(entt::registry& registry,
               const grid_position start,
               const grid_position end) -> comp::line::entity
{
  const auto entity = comp::line::entity{registry.create()};

  auto& line = registry.emplace<comp::line>(entity);
  line.start = start;
  line.end = end;

  return entity;
}

}  // namespace wanderer::sys
