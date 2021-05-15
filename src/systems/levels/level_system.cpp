#include "level_system.hpp"

namespace wanderer::sys {

auto current_level_entity(const entt::registry& shared) -> comp::level::entity
{
  const auto view = shared.view<const comp::level, const comp::active_level>();
  assert(view.size_hint() == 1);
  return comp::level::entity{view.front()};
}

}  // namespace wanderer::sys
