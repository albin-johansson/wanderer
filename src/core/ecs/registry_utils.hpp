#pragma once

#include <concepts>  // convertible_to
#include <entt.hpp>  // registry, entity

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

}  // namespace wanderer
