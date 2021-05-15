#include "level_manager.hpp"

#include <cassert>  // assert
#include <utility>  // move

#include "components/graphics/level_switch_animation.hpp"
#include "components/map/level.hpp"
#include "components/map/portal.hpp"
#include "components/movable.hpp"
#include "components/outside_level.hpp"
#include "components/player.hpp"
#include "core/resources.hpp"
#include "io/map/parse_world.hpp"
#include "systems/graphics/viewport_system.hpp"
#include "systems/levels/level_factory_system.hpp"
#include "systems/levels/level_system.hpp"

namespace wanderer {

[[nodiscard]] inline auto get_id(const comp::level& level) -> int
{
  return level.registry.get<comp::tilemap>(level.tilemap).id;
}

level_manager::level_manager(entt::registry& shared, graphics_context& graphics)
{
  auto worldData = parse_world(resources::map("world.json"));

  const auto worldEntity = shared.create();
  auto& world =
      shared.emplace<comp::level>(worldEntity, sys::make_level(worldData.base, graphics));

  world.id = map_id{get_id(world)};
  world.registry.ctx<ctx::viewport>().keepInBounds = true;

  shared.emplace<comp::outside_level>(worldEntity);

  for (const auto& levelData : worldData.levels)
  {
    const auto e = shared.create();
    auto& sublevel = shared.emplace<comp::level>(e, sys::make_level(levelData, graphics));
    sublevel.id = map_id{get_id(sublevel)};
  }

  shared.emplace<comp::active_level>(worldEntity);
}

}  // namespace wanderer
