#include "tile_object_animation_system.hpp"

#include "animated_tile.hpp"
#include "depth_drawable.hpp"
#include "tile_object.hpp"
#include "tile_rendering_system.hpp"

namespace wanderer::sys {

void update_tile_object_animations(entt::registry& registry)
{
  const auto& tileset = registry.ctx<ctx::tileset>();

  const auto view = registry.view<const comp::tile_object, comp::depth_drawable>();
  for (auto&& [entity, object, drawable] : view.each())
  {
    if (registry.all_of<comp::animated_tile>(object.tileEntity))
    {
      const auto& tile = get_animated_tile(registry, object.tileEntity, tileset);
      drawable.src = tile.src;
    }
  }
}

}  // namespace wanderer::sys