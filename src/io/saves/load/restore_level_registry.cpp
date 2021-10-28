#include "restore_level_registry.hpp"

#include <save.pb.h>

#include <cassert>  // assert

#include "components/ai/humanoid.hpp"
#include "components/player.hpp"
#include "components/tilemap.hpp"
#include "components/tiles/tileset.hpp"
#include "core/ecs/make_registry.hpp"
#include "core/ecs/registry_utils.hpp"
#include "restore_data.hpp"

namespace wanderer {
namespace {

void RestoreTilemap(const proto::level& data, entt::registry& registry)
{
  assert(data.has_id());
  assert(data.has_humanoid_layer_index());
  assert(data.has_row_count());
  assert(data.has_column_count());
  assert(data.has_width());
  assert(data.has_height());

  auto& tilemap = registry.set<comp::Tilemap>();
  tilemap.id = MapID{data.id()};
  tilemap.humanoid_layer = data.humanoid_layer_index();
  tilemap.row_count = data.row_count();
  tilemap.col_count = data.column_count();
  tilemap.size.width = data.width();
  tilemap.size.height = data.height();
}

}  // namespace

auto RestoreLevelRegistry(const proto::level& data) -> entt::registry
{
  auto registry = MakeRegistry();

  RestoreTilemap(data, registry);

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
