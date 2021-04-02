#include "make_registry.hpp"

#include "add_humanoid_state_dependencies.hpp"

namespace wanderer {

auto make_registry() -> entt::registry
{
  entt::registry registry;
  add_humanoid_state_dependencies(registry);
  return registry;
}

}  // namespace wanderer
