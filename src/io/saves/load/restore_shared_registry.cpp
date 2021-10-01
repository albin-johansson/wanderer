#include "restore_shared_registry.hpp"

#include <save.pb.h>

#include "common/map_id.hpp"
#include "components/ctx/level_size.hpp"
#include "components/ctx/time_of_day.hpp"
#include "components/ctx/viewport.hpp"
#include "components/lvl/level.hpp"
#include "components/physics/hitbox.hpp"
#include "components/player.hpp"
#include "components/tiles/tilemap.hpp"
#include "components/tiles/tileset.hpp"
#include "core/day_of_week.hpp"
#include "core/ecs/registry_utils.hpp"
#include "core/utils/centurion_utils.hpp"
#include "restore_level_registry.hpp"
#include "systems/gfx/viewport_system.hpp"

namespace wanderer {
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

void restore(const proto::time_of_day& data, ctx::time_of_day& time)
{
  time.hour = data.hour();
  time.minute = data.minute();
  time.seconds = data.seconds();
  time.week = data.week();
  time.day = static_cast<day_of_week>(data.day());
}

void restore_shared_data(entt::registry& shared, const proto::shared_data& data)
{
  restore(data.time(), shared.set<ctx::time_of_day>());
}

}  // namespace

void restore_shared_registry(entt::registry& shared, const proto::save& save)
{
  shared.clear<comp::level>();
  shared.clear<comp::active_level>();

  restore_shared_data(shared, save.shared());

  for (const auto& levelData : save.levels()) {
    const auto entity = shared.create();

    auto& level = shared.emplace<comp::level>(entity);
    level.tree.disable_thickness_factor();
    level.id = map_id{levelData.id()};
    level.registry = restore_level_registry(levelData);

    if (level.id == save.current_level_id()) {
      shared.emplace<comp::active_level>(entity);
    }

    if (levelData.is_outside_level()) {
      shared.emplace<comp::outside_level>(entity);
    }

    level.tilemap = singleton_entity<comp::tilemap>(level.registry);
    level.tileset = singleton_entity<comp::tileset>(level.registry);

    // TODO maybe<float2> player_spawn_position;

    add_level_size(level);
    add_viewport(level);

    for (auto&& [hitboxEntity, hitbox] : level.registry.view<comp::hitbox>().each()) {
      const auto lower = to_vector(hitbox.bounds.position());
      const auto upper = lower + to_vector(hitbox.bounds.size());
      level.tree.insert(hitboxEntity, lower, upper);
    }

    if constexpr (cen::is_release_build()) {
      level.tree.rebuild();
    }

    {
      auto& viewport = level.registry.ctx<ctx::viewport>();
      viewport.keep_in_bounds = levelData.keep_viewport_in_bounds();
    }

    {
      const auto player = singleton_entity<comp::player>(level.registry);
      const auto& movable = level.registry.get<comp::movable>(player);
      sys::center_viewport_on(level.registry, movable.position);
    }
  }
}

}  // namespace wanderer
