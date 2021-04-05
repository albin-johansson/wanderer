#include "saves_system.hpp"

#include "active_menu.hpp"
#include "animated.hpp"
#include "animated_tile.hpp"
#include "binds.hpp"
#include "chase.hpp"
#include "container_trigger.hpp"
#include "depth_drawable.hpp"
#include "float3.hpp"
#include "hitbox.hpp"
#include "humanoid_state.hpp"
#include "inventory.hpp"
#include "movable.hpp"
#include "object.hpp"
#include "outside_level.hpp"
#include "particle.hpp"
#include "player.hpp"
#include "point_light.hpp"
#include "portal.hpp"
#include "render_bounds.hpp"
#include "spawnpoint.hpp"
#include "tile.hpp"
#include "tile_layer.hpp"
#include "tile_object.hpp"
#include "tilemap.hpp"
#include "tileset.hpp"
#include "time_of_day.hpp"
#include "viewport.hpp"

namespace wanderer::sys {
namespace {

template <typename T, typename Archive>
void process(T& handle, Archive& archive)
{
  handle.entities(archive)
      .template component<ctx::active_menu,
                          ctx::binds,
                          ctx::player,
                          ctx::outside_level,
                          ctx::render_bounds,
                          ctx::tileset,
                          ctx::time_of_day,
                          ctx::viewport,
                          comp::animated,
                          comp::animated_tile,
                          comp::chase,
                          comp::container_trigger,
                          comp::depth_drawable,
                          comp::float3,
                          comp::hitbox,
                          comp::humanoid,
                          comp::humanoid_idle,
                          comp::humanoid_move,
                          comp::humanoid_attack,
                          comp::humanoid_die,
                          comp::inventory,
                          comp::movable,
                          comp::object,
                          comp::particle,
                          comp::portal,
                          comp::point_light,
                          comp::spawnpoint,
                          comp::tile,
                          comp::tile_layer,
                          comp::tile_object,
                          comp::tilemap>(archive);
}

}  // namespace

void save_registry(const entt::registry& registry, output_archive& archive)
{
  entt::snapshot snapshot{registry};
  process(snapshot, archive);
}

auto restore_registry(input_archive& archive) -> entt::registry
{
  entt::registry registry;

  entt::snapshot_loader loader{registry};
  process(loader, archive);

  return registry;
}

}  // namespace wanderer::sys
