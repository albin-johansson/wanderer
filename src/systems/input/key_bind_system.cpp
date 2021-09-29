#include "key_bind_system.hpp"

namespace wanderer::sys {

auto make_bind(entt::registry& registry,
               const cen::scan_code key,
               const menu_action action) -> entt::entity
{
  const auto entity = registry.create();

  auto& bind = registry.emplace<comp::key_bind>(entity);
  bind.key = key;
  bind.action = action;

  return entity;
}

}  // namespace wanderer::sys
