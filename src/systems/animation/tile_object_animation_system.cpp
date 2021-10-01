#include "tile_object_animation_system.hpp"

#include "components/gfx/drawable.hpp"
#include "components/gfx/tile_animation.hpp"
#include "components/tiles/tile_object.hpp"
#include "core/ecs/registry_utils.hpp"
#include "systems/gfx/tile_rendering_system.hpp"

namespace wanderer::sys {

void update_tile_object_animations(entt::registry& registry)
{
  const auto& [tilesetEntity, tileset] = singleton<const comp::tileset>(registry);

  for (auto&& [entity, object, drawable] :
       registry.view<const comp::tile_object, comp::drawable>().each())
  {
    if (registry.all_of<comp::tile_animation>(object.tile_entity)) {
      const auto& tile = get_animated_tile(registry, object.tile_entity, tileset);
      drawable.src = tile.src;
    }
  }
}

}  // namespace wanderer::sys