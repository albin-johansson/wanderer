#include "restore_level_registry.hpp"

#include <save.pb.h>

#include <cassert>  // assert

#include "components/ai/humanoid.hpp"
#include "components/player.hpp"
#include "core/ecs/make_registry.hpp"
#include "restore_data.hpp"

namespace wanderer {

auto RestoreLevelRegistry(const proto::level& data) -> entt::registry
{
  auto registry = MakeRegistry();

  const auto playerEntity = entt::entity{data.player_entity()};

  for (const auto id : data.entities()) {
    const auto hint = entt::entity{id};
    const auto entity = registry.create(hint);
    assert(entity == hint);

    if (entity == playerEntity) {
      assert(registry.empty<comp::Player>());
      registry.emplace<comp::Player>(entity);
    }

    RestoreMovable(data, registry, entity);
    RestoreDrawable(data, registry, entity);
    RestoreAnimation(data, registry, entity);
    RestorePlant(data, registry, entity);
    RestoreTile(data, registry, entity);
    RestoreTilemap(data, registry, entity);
    RestoreTileAnimations(data, registry, entity);
    RestoreParticle(data, registry, entity);
    RestoreLight(data, registry, entity);
    RestoreSpawnpoint(data, registry, entity);
    RestoreHitbox(data, registry, entity);
    RestoreObject(data, registry, entity);
    RestorePortal(data, registry, entity);
    RestoreTileLayer(data, registry, entity);
    RestoreTileset(data, registry, entity);
    RestoreInventory(data, registry, entity);
    RestoreTileObject(data, registry, entity);
    RestoreTrigger(data, registry, entity);
    RestoreAssociation(data, registry, entity);
  }

  /* We need to ensure that all entities are created when restoring these components */
  for (const auto id : data.entities()) {
    RestoreChase(data, registry, entt::entity{id});
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
