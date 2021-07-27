#include "make_registry.hpp"

#include "components/particle.hpp"
#include "core/ecs/add_humanoid_state_dependencies.hpp"

namespace wanderer {

auto make_registry() -> entt::registry
{
  entt::registry registry;

  add_humanoid_state_dependencies(registry);

  // Reserve pools with components that are likely to feature many entities
  registry.reserve<comp::particle>(200);

  return registry;
}

}  // namespace wanderer
