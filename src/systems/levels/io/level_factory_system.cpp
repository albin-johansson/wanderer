#include "level_factory_system.hpp"

#include <centurion.hpp>  // ticks, log
#include <fstream>        // ifstream
#include <ios>            // ios

#include "components/ai/humanoid.hpp"
#include "components/ctx/level_size.hpp"
#include "components/ctx/viewport.hpp"
#include "components/physics/movable.hpp"
#include "components/player.hpp"
#include "components/tiles/tilemap.hpp"
#include "components/tiles/tileset.hpp"
#include "core/ecs/add_humanoid_state_dependencies.hpp"
#include "core/ecs/make_registry.hpp"
#include "core/ecs/registry_utils.hpp"
#include "core/serialization.hpp"
#include "load_ground_layers.hpp"
#include "load_humanoids.hpp"
#include "load_objects.hpp"
#include "load_tile_objects.hpp"
#include "load_tilemap.hpp"
#include "load_tileset.hpp"
#include "load_tileset_textures.hpp"
#include "profile.hpp"
#include "systems/gfx/depth_system.hpp"
#include "systems/gfx/drawable_system.hpp"
#include "systems/gfx/viewport_system.hpp"

namespace wanderer::sys {
namespace {

void add_level_size(comp::Level& level)
{
  const auto& tilemap = level.registry.get<comp::Tilemap>(level.tilemap);
  auto& size = level.registry.set<ctx::LevelSize>();
  size.row_count = tilemap.row_count;
  size.col_count = tilemap.col_count;
}

void add_viewport(comp::Level& level)
{
  const auto& tilemap = level.registry.get<comp::Tilemap>(level.tilemap);
  level.registry.set<ctx::Viewport>(sys::make_viewport(tilemap.size));
}

}  // namespace

auto make_level(const ir::level& data, graphics_context& graphics) -> comp::Level
{
  WANDERER_PROFILE_START

  load_tileset_textures(data, graphics);

  comp::Level level;

  level.tree.disable_thickness_factor();
  level.registry = make_registry();
  level.player_spawn_position = data.player_spawn_point;

  level.tilemap = level.registry.create();
  level.tileset = level.registry.create();

  load_tileset(level.registry, level.tileset, graphics, data.tilesets);
  level.id = load_tilemap(level.registry, level.tilemap, data);

  add_level_size(level);
  add_viewport(level);
  add_ground_layers(level.registry, data);

  load_tile_objects(level, graphics, data);
  load_objects(level.registry, graphics, data);
  load_humanoids(level, graphics);

  sys::center_viewport_on(level.registry, level.player_spawn_position.value());
  sys::update_drawables(level.registry);
  sys::update_depth(level.registry, sys::sort_strategy::std_sort);

  if constexpr (cen::is_release_build()) {
    // This is very slow in debug builds, which is why we avoid it
    level.tree.rebuild();
  }

  WANDERER_PROFILE_END("sys::make_level()")

  return level;
}

}  // namespace wanderer::sys
