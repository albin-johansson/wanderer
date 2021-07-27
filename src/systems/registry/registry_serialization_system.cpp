#include "registry_serialization_system.hpp"

#include "components/animated.hpp"
#include "components/bed_trigger.hpp"
#include "components/chase.hpp"
#include "components/container_trigger.hpp"
#include "components/depth_drawable.hpp"
#include "components/float3.hpp"
#include "components/hitbox.hpp"
#include "components/humanoid_state.hpp"
#include "components/inventory.hpp"
#include "components/movable.hpp"
#include "components/object.hpp"
#include "components/outside_level.hpp"
#include "components/particle.hpp"
#include "components/plant.hpp"
#include "components/player.hpp"
#include "components/point_light.hpp"
#include "components/portal.hpp"
#include "components/spawnpoint.hpp"
#include "components/tile.hpp"
#include "components/tile_animation.hpp"
#include "components/tile_layer.hpp"
#include "components/tile_object.hpp"
#include "components/tilemap.hpp"
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
