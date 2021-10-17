#include "load_humanoids.hpp"

#include "components/ai/humanoid.hpp"
#include "components/gfx/drawable.hpp"
#include "components/lvl/spawnpoint.hpp"
#include "components/tiles/tilemap.hpp"
#include "systems/ai/humanoid/humanoid_factory_system.hpp"

namespace wanderer::sys {
namespace {

void ConfigureHumanoidLayer(entt::registry& registry, const entt::entity tilemapEntity)
{
  const auto& tilemap = registry.get<comp::Tilemap>(tilemapEntity);
  for (auto&& [entity, drawable] : registry.view<comp::Drawable, comp::Humanoid>().each())
  {
    drawable.layer = tilemap.humanoid_layer;
  }
}

}  // namespace

void LoadHumanoids(comp::Level& level, GraphicsContext& graphics)
{
  // The player has to be created before other humanoids!
  sys::MakePlayer(level, graphics);

  for (auto&& [entity, spawnpoint] : level.registry.view<comp::Spawnpoint>().each()) {
    switch (spawnpoint.type) {
      case comp::SpawnpointType::player:
        break;

      case comp::SpawnpointType::skeleton: {
        sys::MakeSkeleton(level, spawnpoint.position, graphics);
        break;
      }
    }
  }

  ConfigureHumanoidLayer(level.registry, level.tilemap);
}

}  // namespace wanderer::sys
