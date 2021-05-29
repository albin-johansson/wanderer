#pragma once

#include <cassert>   // assert
#include <concepts>  // convertible_to
#include <entt.hpp>  // registry, entity
#include <utility>   // pair

#include "core/common_concepts.hpp"

namespace wanderer {

// Destroys all entities in a container, after which the container is cleared
template <container_type<entt::entity> T>
void destroy_and_clear(entt::registry& registry, T& container)
{
  for (const auto entity : container)
  {
    registry.destroy(entity);
  }
  container.clear();
}

template <std::convertible_to<entt::entity> T>
void destroy_if_exists(entt::registry& registry, const T entity)
{
  if (entity != entt::null)
  {
    registry.destroy(entity);
  }
}

template <typename T>
[[nodiscard]] auto singleton_entity(entt::registry& registry) -> entt::entity
{
  const auto view = registry.view<T>();
  assert(view.size() == 1);
  return view.front();
}

template <typename T>
[[nodiscard]] auto singleton_entity(const entt::registry& registry) -> entt::entity
{
  const auto view = registry.view<T>();
  assert(view.size() == 1);
  return view.front();
}

template <typename T>
[[nodiscard]] auto singleton(entt::registry& registry) -> std::pair<entt::entity, T&>
{
  const auto entity = singleton_entity<T>(registry);
  return {entity, registry.get<T>(entity)};
}

template <typename T>
[[nodiscard]] auto singleton(const entt::registry& registry)
    -> std::pair<entt::entity, const T&>
{
  const auto entity = singleton_entity<T>(registry);
  return {entity, registry.get<T>(entity)};
}

}  // namespace wanderer
