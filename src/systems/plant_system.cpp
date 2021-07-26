#include "plant_system.hpp"

#include "components/graphics/depth_drawable.hpp"
#include "components/plant.hpp"
#include "systems/tiles/tile_system.hpp"

namespace wanderer::sys {

void update_plants(entt::registry& registry, const rune::delta_time dt)
{
  for (auto&& [entity, plant] : registry.view<comp::plant>().each())
  {
    plant.current += plant.rate * dt;

    if (plant.current >= plant.rate)
    {
      ++plant.index;
      plant.current = 0;
      plant.index %= plant.tiles.size();
    }

    if (auto* drawable = registry.try_get<comp::depth_drawable>(entity))
    {
      const auto id = plant.tiles.at(plant.index);
      const auto& tile = get_tile(registry, id);
      drawable->src = tile.src;
    }
  }
}

}  // namespace wanderer::sys
