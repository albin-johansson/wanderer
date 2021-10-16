#include "load_humanoids.hpp"

#include "components/ai/humanoid.hpp"
#include "components/gfx/drawable.hpp"
#include "components/lvl/spawnpoint.hpp"
#include "components/tiles/tilemap.hpp"
#include "systems/ai/humanoid/humanoid_factory_system.hpp"

namespace wanderer::sys {
namespace {

void configure_humanoid_layer(entt::registry& registry, const entt::entity tilemapEntity)
{
  const auto& tilemap = registry.get<comp::Tilemap>(tilemapEntity);
  for (auto&& [entity, drawable] : registry.view<comp::Drawable, comp::Humanoid>().each())
  {
    drawable.layer = tilemap.humanoid_layer;
  }
}

}  // namespace

void load_humanoids(comp::Level& level, graphics_context& graphics)
{
  // The player has to be created before other humanoids!
  sys::make_player(level, graphics);

  for (auto&& [entity, spawnpoint] : level.registry.view<comp::Spawnpoint>().each()) {
    switch (spawnpoint.type) {
      case comp::SpawnpointType::player:
        break;

      case comp::SpawnpointType::skeleton: {
        sys::make_skeleton(level, spawnpoint.position, graphics);
        break;
      }
    }
  }

  configure_humanoid_layer(level.registry, level.tilemap);
}

}  // namespace wanderer::sys
