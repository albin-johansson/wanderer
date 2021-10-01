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
#include "core/ecs/registry_utils.hpp"
#include "core/utils/centurion_utils.hpp"
#include "restore_data.hpp"
#include "restore_level_registry.hpp"
#include "systems/gfx/viewport_system.hpp"

namespace wanderer {
namespace {

void restore_shared_data(entt::registry& shared, const proto::shared_data& data)
{
  shared.clear<comp::level>();
  shared.clear<comp::active_level>();

  shared.set<ctx::time_of_day>(restore(data.time()));
}

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

void restore_aabb_tree(entt::registry& registry, aabb_tree& tree)
{
  for (auto&& [hitboxEntity, hitbox] : registry.view<comp::hitbox>().each()) {
    const auto lower = to_vector(hitbox.bounds.position());
    const auto upper = lower + to_vector(hitbox.bounds.size());
    tree.insert(hitboxEntity, lower, upper);
  }

  if constexpr (cen::is_release_build()) {
    tree.rebuild();
  }
}

void prepare_viewport(entt::registry& registry, const bool keepInBounds)
{
  auto& viewport = registry.ctx<ctx::viewport>();
  viewport.keep_in_bounds = keepInBounds;

  const auto player = singleton_entity<comp::player>(registry);
  const auto& movable = registry.get<comp::movable>(player);
  sys::center_viewport_on(registry, movable.position);
}

}  // namespace

void restore_shared_registry(entt::registry& shared, const proto::save& save)
{
  restore_shared_data(shared, save.shared());

  for (const auto& data : save.levels()) {
    const auto entity = shared.create();

    auto& level = shared.emplace<comp::level>(entity);
    level.id = map_id{data.id()};

    if (level.id == save.current_level_id()) {
      shared.emplace<comp::active_level>(entity);
    }

    if (data.is_outside_level()) {
      shared.emplace<comp::outside_level>(entity);
    }

    level.tree.disable_thickness_factor();
    level.registry = restore_level_registry(data);
    level.tilemap = singleton_entity<comp::tilemap>(level.registry);
    level.tileset = singleton_entity<comp::tileset>(level.registry);

    // TODO maybe<float2> player_spawn_position;

    add_level_size(level);
    add_viewport(level);

    restore_aabb_tree(level.registry, level.tree);
    prepare_viewport(level.registry, data.keep_viewport_in_bounds());
  }
}

}  // namespace wanderer
