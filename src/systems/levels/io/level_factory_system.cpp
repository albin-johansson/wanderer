#include "level_factory_system.hpp"

#include <centurion.hpp>  // ticks, log
#include <fstream>        // ifstream
#include <ios>            // ios

#include "components/ai/humanoid_state.hpp"
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
#include "systems/graphics/depth_system.hpp"
#include "systems/graphics/drawable_system.hpp"
#include "systems/graphics/viewport_system.hpp"
#include "systems/registry/registry_serialization_system.hpp"

namespace wanderer::sys {
namespace {

void add_level_size(comp::level& level)
{
  const auto& tilemap = level.registry.get<comp::tilemap>(level.tilemap);
  auto& size = level.registry.set<ctx::level_size>();
  size.row_count = tilemap.row_count;
  size.col_count = tilemap.col_count;
}

void add_viewport(comp::level& level)
{
  const auto& tilemap = level.registry.get<comp::tilemap>(level.tilemap);
  level.registry.set<ctx::viewport>(sys::make_viewport(tilemap.size));
}

}  // namespace

auto make_level(const ir::level& data, graphics_context& graphics) -> comp::level
{
  WANDERER_PROFILE_START

  load_tileset_textures(data, graphics);

  comp::level level;

  level.tree.disable_thickness_factor();
  level.registry = make_registry();
  level.player_spawn_position = data.player_spawn_point;

  level.tilemap = comp::tilemap::entity{level.registry.create()};
  level.tileset = comp::tileset::entity{level.registry.create()};

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
  sys::sort_depth_drawables(level.registry, sys::sort_strategy::std_sort);

  if constexpr (cen::is_release_build()) {
    // This is very slow in debug builds, which is why we avoid it
    level.tree.rebuild();
  }

  WANDERER_PROFILE_END("sys::make_level()")

  return level;
}

auto restore_level(const std::filesystem::path& path, graphics_context& graphics)
    -> comp::level
{
  WANDERER_PROFILE_START

  comp::level level;

  std::ifstream stream{path, std::ios::binary};
  input_archive archive{stream};

  // Do not change order!
  level.registry = sys::restore_registry(archive);
  archive(level.tree);
  archive(level.tilemap);
  archive(level.player_spawn_position);

  add_humanoid_state_dependencies(level.registry);

  add_level_size(level);
  add_viewport(level);

  const auto player = singleton_entity<comp::player>(level.registry);
  const auto& movable = level.registry.get<comp::movable>(player);
  center_viewport_on(level.registry, movable.position);

  WANDERER_PROFILE_END("sys::restore_level()")

  return level;
}

}  // namespace wanderer::sys
