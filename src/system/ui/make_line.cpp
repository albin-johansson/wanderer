#include "make_line.hpp"

namespace wanderer::sys {

auto make_line(entt::registry& registry,
               const cen::ipoint start,
               const cen::ipoint end) -> comp::line::entity
{
  const auto entity = registry.create();
  auto& line = registry.emplace<comp::line>(entity);

  line.start = cen::cast<cen::fpoint>(start);
  line.end = cen::cast<cen::fpoint>(end);

  return comp::line::entity{entity};
}

}  // namespace wanderer::sys
