#include "load_levels.hpp"

#include <filesystem>  // path, absolute

#include <tactile-io/parser.hpp>

#include "components/humanoid.hpp"
#include "components/level.hpp"
#include "components/level_size.hpp"
#include "components/portal.hpp"
#include "components/tilemap.hpp"
#include "components/viewport.hpp"
#include "core/ecs/make_registry.hpp"
#include "core/resources.hpp"
#include "create_humanoids.hpp"
#include "create_layers.hpp"
#include "create_tileset.hpp"
#include "profile.hpp"
#include "systems/gfx/depth_system.hpp"
#include "systems/gfx/drawable_system.hpp"
#include "systems/gfx/viewport_system.hpp"
#include "tactile_io_utils.hpp"
#include "wanderer_std.hpp"

namespace wanderer {
namespace {

void AddLevelMetaInformation(const Tactile::IO::Map& irMap, comp::Level& level)
{
  auto& registry = level.registry;

  auto& tilemap = registry.set<comp::Tilemap>();
  tilemap.id = MapID{level.id};
  tilemap.row_count = Tactile::IO::GetRowCount(irMap);
  tilemap.col_count = Tactile::IO::GetColumnCount(irMap);
  tilemap.size = {static_cast<float>(tilemap.col_count) * glob::tile_width<float>,
                  static_cast<float>(tilemap.row_count) * glob::tile_height<float>};
  tilemap.humanoid_layer = GetInt(irMap, "humanoidLayer");

  auto& size = registry.set<ctx::LevelSize>();
  size.row_count = tilemap.row_count;
  size.col_count = tilemap.col_count;

  registry.set<ctx::Viewport>(sys::MakeViewport(tilemap.size));
}

auto LoadLevel(entt::registry& shared,
               GraphicsContext& graphics,
               const std::filesystem::path& path) -> entt::entity
{
  WANDERER_PROFILE_START

  Tactile::IO::ParseError error{};
  if (const auto irMap = Tactile::IO::ParseMap(path, &error)) {
    const auto id = MapID(GetInt(*irMap, "id"));

    for (auto&& [entity, level] : shared.view<comp::Level>().each()) {
      if (level.id == id) {
        return entity;
      }
    }

    CENTURION_LOG_DEBUG("Loading level %s", path.string().c_str());

    LoadTilesetTextures(*irMap, graphics);

    const auto levelEntity = shared.create();
    auto& level = shared.emplace<comp::Level>(levelEntity);
    level.id = id;
    level.registry = MakeRegistry();
    level.tree.disable_thickness_factor();

    if (GetBool(*irMap, "is-outside")) {
      shared.emplace<comp::OutsideLevel>(levelEntity);
    }

    AddLevelMetaInformation(*irMap, level);
    CreateTileset(*irMap, level, graphics);
    CreateLayers(*irMap, level, graphics);
    CreateHumanoids(*irMap, level, graphics);

    sys::CenterViewportOn(level.registry, level.player_spawn_position.value());
    sys::UpdateDrawables(level.registry);
    sys::UpdateDepth(level.registry, sys::SortStrategy::StdSort);

    if constexpr (cen::is_release_build()) {
      /* This is very slow in debug builds, so we avoid it */
      level.tree.rebuild();
    }

    WANDERER_PROFILE_END("Loaded level")

    for (auto&& [entity, portal] : level.registry.view<comp::Portal>().each()) {
      if (!portal.path.empty() && portal.path != ".") {
        LoadLevel(shared, graphics, path.parent_path() / portal.path);
      }
    }

    return levelEntity;
  }
  else {
    CENTURION_LOG_ERROR("An error occurred when parsing a level: %s",
                        Tactile::IO::GetCause(error));
    throw WandererError{"Failed to parse map!"};
  }
}

}  // namespace

void LoadLevels(entt::registry& shared, GraphicsContext& graphics)
{
  const auto path = std::filesystem::absolute(resources::map("main.json"));
  const auto root = LoadLevel(shared, graphics, path);
  shared.emplace<comp::ActiveLevel>(root);

  auto& rootLevel = shared.get<comp::Level>(root);
  rootLevel.registry.ctx<ctx::Viewport>().keep_in_bounds = true;
}

}  // namespace wanderer
