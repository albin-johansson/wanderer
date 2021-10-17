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

void AddLevelSize(comp::Level& level)
{
  const auto& tilemap = level.registry.get<comp::Tilemap>(level.tilemap);
  auto& size = level.registry.set<ctx::LevelSize>();
  size.row_count = tilemap.row_count;
  size.col_count = tilemap.col_count;
}

void AddViewport(comp::Level& level)
{
  const auto& tilemap = level.registry.get<comp::Tilemap>(level.tilemap);
  level.registry.set<ctx::Viewport>(sys::MakeViewport(tilemap.size));
}

}  // namespace

auto MakeLevel(const ir::level& data, GraphicsContext& graphics) -> comp::Level
{
  WANDERER_PROFILE_START

  LoadTilesetTextures(data, graphics);

  comp::Level level;

  level.tree.disable_thickness_factor();
  level.registry = MakeRegistry();
  level.player_spawn_position = data.player_spawn_point;

  level.tilemap = level.registry.create();
  level.tileset = level.registry.create();

  LoadTileset(level.registry, level.tileset, graphics, data.tilesets);
  level.id = LoadTilemap(level.registry, level.tilemap, data);

  AddLevelSize(level);
  AddViewport(level);
  AddGroundLayers(level.registry, data);

  LoadTileObjects(level, graphics, data);
  LoadObjects(level.registry, graphics, data);
  LoadHumanoids(level, graphics);

  sys::CenterViewportOn(level.registry, level.player_spawn_position.value());
  sys::UpdateDrawables(level.registry);
  sys::UpdateDepth(level.registry, sys::SortStrategy::StdSort);

  if constexpr (cen::is_release_build()) {
    // This is very slow in debug builds, which is why we avoid it
    level.tree.rebuild();
  }

  WANDERER_PROFILE_END("sys::MakeLevel()")

  return level;
}

}  // namespace wanderer::sys
