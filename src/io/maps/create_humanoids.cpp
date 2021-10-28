#include "create_humanoids.hpp"

#include "components/ai/humanoid.hpp"
#include "components/gfx/drawable.hpp"
#include "components/lvl/spawnpoint.hpp"
#include "components/tiles/tilemap.hpp"
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

  const auto& tilemap = level.registry.get<comp::Tilemap>(level.tilemap);
  for (auto&& [entity, drawable] :
       level.registry.view<comp::Drawable, comp::Humanoid>().each())
  {
    drawable.layer = tilemap.humanoid_layer;
  }
}

}  // namespace wanderer
