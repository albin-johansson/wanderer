#include "registry_system.hpp"

#include "wanderer/data/cfg.hpp"
#include "wanderer/data/components/levels.hpp"
#include "wanderer/data/components/rendering.hpp"
#include "wanderer/data/components/tiles.hpp"
#include "ui_system.hpp"

namespace wanderer::sys {

auto make_main_registry(const game_cfg& cfg) -> entt::registry
{
  entt::registry registry;

  registry.set<game_cfg>(cfg);
  registry.set<comp::level_ctx>();

  load_menus(registry);

  return registry;
}

auto make_level_registry(const game_cfg& cfg) -> entt::registry
{
  entt::registry registry;

  registry.set<game_cfg>(cfg);
  registry.set<comp::tilemap>();
  registry.set<comp::tilesets>();
  registry.set<comp::render_bounds>();

  auto& viewport = registry.set<comp::viewport>();
  viewport.size = cfg.logical_size_f;

  return registry;
}

}  // namespace wanderer::sys