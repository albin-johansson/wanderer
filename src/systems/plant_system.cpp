#include "plant_system.hpp"

#include <algorithm>  // find

#include "components/depth_drawable.hpp"
#include "components/plant.hpp"
#include "core/game_constants.hpp"
#include "systems/tiles/tile_system.hpp"

namespace wanderer::sys {
namespace {

void update_plant_drawable(entt::registry& registry,
                           const comp::plant& plant,
                           comp::depth_drawable& drawable)
{
  const auto id = plant.tiles.at(plant.index);

  // If the current tile is tall, offset destination position and size.
  if (std::ranges::find(plant.tall, id) != plant.tall.end())
  {
    drawable.dst.set_y(plant.base_y - glob::tile_height<float>);
    drawable.dst.set_height(2.0f * glob::tile_height<float>);
  }
  else
  {
    drawable.dst.set_y(plant.base_y);
    drawable.dst.set_height(glob::tile_height<float>);
  }

  const auto& tile = get_tile(registry, id);
  drawable.src = tile.src;

  if (drawable.dst.y() != plant.base_y)
  {
    drawable.src.set_y(drawable.src.y() - plant.tile_height);
    drawable.src.set_height(2 * plant.tile_height);
  }
}

}  // namespace

void update_plants(entt::registry& registry, const rune::delta_time dt)
{
  for (auto&& [entity, plant] : registry.view<comp::plant>().each())
  {
    if (plant.index < plant.tiles.size() - 1)
    {
      plant.current += plant.rate * dt;
      if (plant.current >= plant.rate)
      {
        plant.current = 0;
        ++plant.index;
      }
    }
    else
    {
      // TODO the plant is ripe here
    }

    if (auto* drawable = registry.try_get<comp::depth_drawable>(entity))
    {
      update_plant_drawable(registry, plant, *drawable);
    }
  }
}

}  // namespace wanderer::sys
