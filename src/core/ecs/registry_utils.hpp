#pragma once

#include <entt.hpp>  // registry

#include "common_concepts.hpp"

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

}  // namespace wanderer
