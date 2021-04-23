#include "line_factory_system.hpp"

namespace wanderer::sys {

auto make_line(entt::registry& registry, const cen::fpoint start, const cen::fpoint end)
    -> comp::line::entity
{
  const auto entity = comp::line::entity{registry.create()};

  auto& line = registry.emplace<comp::line>(entity);
  line.start = start;
  line.end = end;

  return entity;
}

}  // namespace wanderer::sys
