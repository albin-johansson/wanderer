#include "level_system.hpp"

namespace wanderer::sys {
namespace {

[[nodiscard]] auto current_level_entity(const entt::registry& shared)
    -> comp::level::entity
{
  const auto view = shared.view<const comp::level, const comp::active_level>();
  assert(view.size_hint() == 1);
  return comp::level::entity{view.front()};
}

}  // namespace

auto current_level(entt::registry& shared) -> comp::level&
{
  return shared.get<comp::level>(current_level_entity(shared));
}

auto current_level(const entt::registry& shared) -> const comp::level&
{
  return shared.get<comp::level>(current_level_entity(shared));
}

}  // namespace wanderer::sys
