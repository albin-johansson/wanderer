#include "create_humanoids.hpp"

#include "components/drawable.hpp"
#include "components/humanoid.hpp"
#include "components/spawnpoint.hpp"
#include "components/tilemap.hpp"
#include "systems/ai/humanoid/humanoid_factory_system.hpp"

namespace wanderer {

void CreateHumanoids(const Tactile::IO::Map& irMap,
                     comp::Level& level,
                     GraphicsContext& graphics)

{
  /* The player has to be created before other humanoids! */
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

  const auto& tilemap = level.registry.ctx<comp::Tilemap>();
  for (auto&& [entity, drawable] :
       level.registry.view<comp::Drawable, comp::Humanoid>().each())
  {
    drawable.layer = tilemap.humanoid_layer;
  }
}

}  // namespace wanderer
