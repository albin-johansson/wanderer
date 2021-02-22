#pragma once

#include <cassert>   // assert
#include <entt.hpp>  // registry

namespace wanderer {

template <typename Component>
[[nodiscard]] auto singleton(entt::registry& registry) -> Component&
{
  const auto view = registry.view<Component>();
  assert(view.size() == 1);

  return registry.get<Component>(view.front());
}

template <typename Component>
[[nodiscard]] auto singleton(const entt::registry& registry) -> const Component&
{
  const auto view = registry.view<const Component>();
  assert(view.size() == 1);

  return registry.get<const Component>(view.front());
}

}  // namespace wanderer
