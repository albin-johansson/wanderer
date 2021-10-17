#include "tile_object_animation_system.hpp"

#include "components/gfx/drawable.hpp"
#include "components/gfx/tile_animation.hpp"
#include "components/tiles/tile_object.hpp"
#include "core/ecs/registry_utils.hpp"
#include "systems/gfx/tile_rendering_system.hpp"

namespace wanderer::sys {

void UpdateTileObjectAnimations(entt::registry& registry)
{
  const auto& [tilesetEntity, tileset] = singleton<const comp::Tileset>(registry);

  for (auto&& [entity, object, drawable] :
       registry.view<const comp::TileObject, comp::Drawable>().each())
  {
    if (registry.all_of<comp::TileAnimation>(object.tile_entity)) {
      const auto& tile = GetAnimatedTile(registry, object.tile_entity, tileset);
      drawable.src = tile.src;
    }
  }
}

}  // namespace wanderer::sys