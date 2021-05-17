#include "level_system.hpp"

#include "components/outside_level.hpp"
#include "core/ecs/registry_utils.hpp"

namespace wanderer::sys {

auto current_level(entt::registry& shared) -> comp::level&
{
  return shared.get<comp::level>(singleton_entity<const comp::active_level>(shared));
}

auto current_level(const entt::registry& shared) -> const comp::level&
{
  return shared.get<comp::level>(singleton_entity<const comp::active_level>(shared));
}

auto is_current_level_outside(const entt::registry& shared) -> bool
{
  const auto level = singleton_entity<const comp::active_level>(shared);
  return shared.all_of<comp::outside_level>(level);
}

}  // namespace wanderer::sys
