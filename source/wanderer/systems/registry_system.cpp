#include "registry_system.hpp"

#include "physics_system.hpp"
#include "ui_system.hpp"
#include "wanderer/data/cfg.hpp"
#include "wanderer/data/components/levels.hpp"
#include "wanderer/data/components/rendering.hpp"
#include "wanderer/data/components/tiles.hpp"
#include "wanderer/data/components/world.hpp"

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
  registry.set<comp::tileset>();
  registry.set<comp::render_bounds>();

  // TODO remember to sync this when switching active levels
  auto& date = registry.set<comp::date_and_time>();
  date.day = day_of_week::monday;
  date.hour = 0;
  date.minute = 0;
  date.seconds = 14.0f * 3'600.0f;
  date.tint = cen::colors::transparent;

  auto& viewport = registry.set<comp::viewport>();
  viewport.size = cfg.logical_size_f;

  registry.on_destroy<comp::physics_body>().connect<&sys::on_destroy_physics_object>();

  auto& world = registry.set<comp::physics_world>();

  /* Assume that a tile is 1x1 meters */
  world.scale.x = 1.0f / cfg.tile_size.x;
  world.scale.y = 1.0f / cfg.tile_size.y;

  return registry;
}

}  // namespace wanderer::sys