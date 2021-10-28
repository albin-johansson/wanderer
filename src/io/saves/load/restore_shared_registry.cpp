#include "restore_shared_registry.hpp"

#include <save.pb.h>

#include "components/hitbox.hpp"
#include "components/level.hpp"
#include "components/level_size.hpp"
#include "components/movable.hpp"
#include "components/player.hpp"
#include "components/tilemap.hpp"
#include "components/tileset.hpp"
#include "components/time_of_day.hpp"
#include "components/viewport.hpp"
#include "core/ecs/registry_utils.hpp"
#include "core/utils/centurion_utils.hpp"
#include "restore_data.hpp"
#include "restore_level_registry.hpp"
#include "systems/gfx/viewport_system.hpp"
#include "wanderer_std.hpp"

namespace wanderer {
namespace {

void RestoreSharedData(entt::registry& shared, const proto::SharedData& data)
{
  shared.clear<comp::Level>();
  shared.clear<comp::ActiveLevel>();

  shared.set<ctx::TimeOfDay>(Restore(data.time()));
}

void AddLevelSize(comp::Level& level)
{
  const auto& tilemap = level.registry.ctx<comp::Tilemap>();
  auto& size = level.registry.set<ctx::LevelSize>();
  size.row_count = tilemap.row_count;
  size.col_count = tilemap.col_count;
}

void AddViewport(comp::Level& level)
{
  const auto& tilemap = level.registry.ctx<comp::Tilemap>();
  level.registry.set<ctx::Viewport>(sys::MakeViewport(tilemap.size));
}

void RestoreAabbTree(entt::registry& registry, aabb_tree& tree)
{
  for (auto&& [hitboxEntity, hitbox] : registry.view<comp::Hitbox>().each()) {
    const auto lower = to_rune_vector(hitbox.bounds.position());
    const auto upper = lower + to_rune_vector(hitbox.bounds.size());
    tree.insert(hitboxEntity, lower, upper);
  }

  if constexpr (cen::is_release_build()) {
    tree.rebuild();
  }
}

void PrepareViewport(entt::registry& registry, const bool keepInBounds)
{
  auto& viewport = registry.ctx<ctx::Viewport>();
  viewport.keep_in_bounds = keepInBounds;

  const auto player = singleton_entity<comp::Player>(registry);
  const auto& movable = registry.get<comp::Movable>(player);
  sys::CenterViewportOn(registry, movable.position);
}

}  // namespace

void RestoreSharedRegistry(entt::registry& shared, const proto::Save& save)
{
  RestoreSharedData(shared, save.shared());

  for (const auto& data : save.levels()) {
    const auto entity = shared.create();

    auto& level = shared.emplace<comp::Level>(entity);
    level.id = MapID{data.id()};

    if (level.id == save.current_level_id()) {
      shared.emplace<comp::ActiveLevel>(entity);
    }

    if (data.is_outside_level()) {
      shared.emplace<comp::OutsideLevel>(entity);
    }

    level.tree.disable_thickness_factor();
    level.registry = RestoreLevelRegistry(data);
    level.tileset = singleton_entity<comp::Tileset>(level.registry);

    // TODO maybe<float2> player_spawn_position;

    AddLevelSize(level);
    AddViewport(level);

    RestoreAabbTree(level.registry, level.tree);
    PrepareViewport(level.registry, data.keep_viewport_in_bounds());
  }
}

}  // namespace wanderer
