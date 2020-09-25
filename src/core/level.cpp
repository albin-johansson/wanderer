#include "level.hpp"

#include "add_humanoid_state_dependencies.hpp"

namespace wanderer {
namespace {

[[nodiscard]] auto make_registry() -> entt::registry
{
  entt::registry registry;
  add_humanoid_state_dependencies(registry);
  return registry;
}

}  // namespace

level::level() : m_registry{make_registry()}
{}

}  // namespace wanderer
