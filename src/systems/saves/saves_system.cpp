#include "saves_system.hpp"

#include "animated.hpp"
#include "animated_tile.hpp"
#include "binds.hpp"
#include "chase.hpp"
#include "container_trigger.hpp"
#include "depth_drawable.hpp"
#include "hitbox.hpp"
#include "humanoid_state.hpp"
#include "inventory.hpp"
#include "movable.hpp"
#include "object.hpp"
#include "player.hpp"
#include "portal.hpp"
#include "spawnpoint.hpp"
#include "tile.hpp"
#include "tile_layer.hpp"
#include "tile_object.hpp"
#include "tilemap.hpp"
#include "tileset.hpp"

namespace wanderer::sys {
namespace {

template <typename T, typename Archive>
void process(T& handle, Archive& archive)
{
  handle.entities(archive)
      .template component<comp::animated,
                          comp::animated_tile,
                          comp::binds,
                          comp::chase,
                          comp::container_trigger,
                          comp::depth_drawable,
                          comp::hitbox,
                          comp::humanoid,
                          comp::humanoid_idle,
                          comp::humanoid_move,
                          comp::humanoid_attack,
                          comp::humanoid_die,
                          comp::inventory,
                          comp::movable,
                          comp::object,
                          comp::player,
                          comp::portal,
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
