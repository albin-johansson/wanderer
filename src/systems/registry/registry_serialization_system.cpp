#include "registry_serialization_system.hpp"

#include "components/bed_trigger.hpp"
#include "components/chase.hpp"
#include "components/ctx/active_menu.hpp"
#include "components/ctx/binds.hpp"
#include "components/ctx/render_bounds.hpp"
#include "components/ctx/time_of_day.hpp"
#include "components/ctx/viewport.hpp"
#include "components/float3.hpp"
#include "components/graphics/animated.hpp"
#include "components/graphics/depth_drawable.hpp"
#include "components/graphics/particle.hpp"
#include "components/graphics/point_light.hpp"
#include "components/graphics/tile_animation.hpp"
#include "components/hitbox.hpp"
#include "components/humanoid_state.hpp"
#include "components/inventory/container_trigger.hpp"
#include "components/inventory/inventory.hpp"
#include "components/map/portal.hpp"
#include "components/map/spawnpoint.hpp"
#include "components/map/tile.hpp"
#include "components/map/tile_layer.hpp"
#include "components/map/tile_object.hpp"
#include "components/map/tilemap.hpp"
#include "components/movable.hpp"
#include "components/object.hpp"
#include "components/outside_level.hpp"
#include "components/player.hpp"
#include "components/tileset.hpp"

namespace wanderer::sys {
namespace {

template <typename T, typename Archive>
void process(T& handle, Archive& archive)
{
  handle.entities(archive)
      .template component<comp::animated,
                          comp::bed_trigger,
                          comp::tile_animation,
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
                          comp::outside_level,
                          comp::particle,
                          comp::portal,
                          comp::point_light,
                          comp::player,
                          comp::spawnpoint,
                          comp::tile,
                          comp::tile_layer,
                          comp::tile_object,
                          comp::tilemap,
                          comp::tileset>(archive);
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
