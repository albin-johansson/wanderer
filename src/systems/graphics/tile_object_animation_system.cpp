#include "tile_object_animation_system.hpp"

#include "components/graphics/depth_drawable.hpp"
#include "components/graphics/tile_animation.hpp"
#include "components/map/tile_object.hpp"
#include "core/ecs/registry_utils.hpp"
#include "systems/graphics/tile_rendering_system.hpp"

namespace wanderer::sys {

void update_tile_object_animations(entt::registry& registry)
{
  const auto& tileset = singleton<const comp::tileset>(registry);

  for (auto&& [entity, object, drawable] :
       registry.view<const comp::tile_object, comp::depth_drawable>().each())
  {
    if (registry.all_of<comp::tile_animation>(object.tileEntity))
    {
      const auto& tile = get_animated_tile(registry, object.tileEntity, tileset);
      drawable.src = tile.src;
    }
  }
}

}  // namespace wanderer::sys