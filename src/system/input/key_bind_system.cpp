#include "key_bind_system.hpp"

#include "create_action.hpp"

namespace wanderer::sys {

auto make_bind(entt::registry& registry,
               const cen::scan_code key,
               const menu_action action) -> comp::key_bind::entity
{
  const auto entity = registry.create();

  auto& bind = registry.emplace<comp::key_bind>(entity);
  bind.key = key;
  bind.action = create_action(action);

  return comp::key_bind::entity{entity};
}

}  // namespace wanderer::sys
