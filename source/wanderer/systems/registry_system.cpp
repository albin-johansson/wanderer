#include "registry_system.hpp"

#include "wanderer/data/components/tiles.hpp"

namespace wanderer::sys {

auto make_main_registry() -> entt::registry
{
  entt::registry registry;

  return registry;
}

auto make_level_registry() -> entt::registry
{
  entt::registry registry;

  registry.set<comp::tilemap>();
  registry.set<comp::tilesets>();

  return registry;
}

}  // namespace wanderer::sys