#include "load_humanoids.hpp"

#include "components/ai/humanoid.hpp"
#include "components/gfx/depth_drawable.hpp"
#include "components/lvl/spawnpoint.hpp"
#include "components/tiles/tilemap.hpp"
#include "systems/humanoid/humanoid_factory_system.hpp"

namespace wanderer::sys {
namespace {

void configure_humanoid_layer(entt::registry& registry,
                              const comp::tilemap::entity entity)
{
  const auto& tilemap = registry.get<comp::tilemap>(entity);
  for (auto&& [entity, drawable] :
       registry.view<comp::depth_drawable, comp::humanoid>().each())
  {
    drawable.layer = tilemap.humanoid_layer;
  }
}

}  // namespace

void load_humanoids(comp::level& level, graphics_context& graphics)
{
  // The player has to be created before other humanoids!
  sys::make_player(level, graphics);

  for (auto&& [entity, spawnpoint] : level.registry.view<comp::spawnpoint>().each()) {
    switch (spawnpoint.type) {
      case comp::spawnpoint_type::player:
        break;

      case comp::spawnpoint_type::skeleton: {
        sys::make_skeleton(level, spawnpoint.position, graphics);
        break;
      }
    }
  }

  configure_humanoid_layer(level.registry, level.tilemap);
}

}  // namespace wanderer::sys
