#include "restore_level_registry.hpp"

#include <save.pb.h>

#include <cassert>  // assert

#include "components/ai/humanoid.hpp"
#include "components/player.hpp"
#include "core/ecs/make_registry.hpp"
#include "restore_data.hpp"

namespace wanderer {

auto restore_level_registry(const proto::level& data) -> entt::registry
{
  auto registry = make_registry();

  const auto playerEntity = entt::entity{data.player_entity()};

  for (const auto id : data.entities()) {
    const auto hint = entt::entity{id};
    const auto entity = registry.create(hint);
    assert(entity == hint);

    if (entity == playerEntity) {
      assert(registry.empty<comp::Player>());
      registry.emplace<comp::Player>(entity);
    }

    restore_movable(data, registry, entity);
    restore_drawable(data, registry, entity);
    restore_animation(data, registry, entity);
    restore_plant(data, registry, entity);
    restore_tile(data, registry, entity);
    restore_tilemap(data, registry, entity);
    restore_tile_animations(data, registry, entity);
    restore_particle(data, registry, entity);
    restore_light(data, registry, entity);
    restore_spawnpoint(data, registry, entity);
    restore_hitbox(data, registry, entity);
    restore_object(data, registry, entity);
    restore_portal(data, registry, entity);
    restore_tile_layer(data, registry, entity);
    restore_tileset(data, registry, entity);
    restore_inventory(data, registry, entity);
    restore_tile_object(data, registry, entity);
    restore_trigger(data, registry, entity);
    restore_association(data, registry, entity);
  }

  /* We need to ensure that all entities are created when restoring these components */
  for (const auto id : data.entities()) {
    restore_chase(data, registry, entt::entity{id});
  }

  for (const auto id : data.humanoids()) {
    const auto entity = entt::entity{id};
    assert(registry.valid(entity));

    registry.emplace<comp::HumanoidIdle>(entity);
    registry.emplace<comp::Humanoid>(entity);
  }

  return registry;
}

}  // namespace wanderer
