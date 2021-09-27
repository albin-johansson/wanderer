#include "registry_serialization_system.hpp"

#include "components/ai/chase.hpp"
#include "components/ai/humanoid_state.hpp"
#include "components/gfx/animated.hpp"
#include "components/gfx/depth_drawable.hpp"
#include "components/gfx/point_light.hpp"
#include "components/gfx/tile_animation.hpp"
#include "components/items/container_ref.hpp"
#include "components/items/inventory.hpp"
#include "components/lvl/outside_level.hpp"
#include "components/lvl/portal.hpp"
#include "components/lvl/spawnpoint.hpp"
#include "components/object.hpp"
#include "components/physics/float3.hpp"
#include "components/physics/hitbox.hpp"
#include "components/physics/movable.hpp"
#include "components/physics/particle.hpp"
#include "components/plant.hpp"
#include "components/player.hpp"
#include "components/tiles/tile.hpp"
#include "components/tiles/tile_layer.hpp"
#include "components/tiles/tile_object.hpp"
#include "components/tiles/tilemap.hpp"
#include "components/tiles/tileset.hpp"
#include "components/trigger.hpp"

namespace wanderer::sys {
namespace {

template <typename T, typename Archive>
void process(T& handle, Archive& archive)
{
  handle.entities(archive)
      .template component<comp::animated,
                          comp::trigger,
                          comp::tile_animation,
                          comp::chase,
                          comp::container_ref,
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
                          comp::plant,
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
