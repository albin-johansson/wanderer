#include "key_bind_system.hpp"

namespace wanderer::sys {

auto MakeBind(entt::registry& registry, cen::scan_code key, MenuAction action)
    -> entt::entity
{
  const auto entity = registry.create();

  auto& bind = registry.emplace<comp::KeyBind>(entity);
  bind.key = key;
  bind.action = action;

  return entity;
}

}  // namespace wanderer::sys
