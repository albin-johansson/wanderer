#include "tile_system.hpp"

#include "components/tiles/tileset.hpp"
#include "core/ecs/registry_utils.hpp"

namespace wanderer::sys {

auto get_tile(entt::registry& registry, const tile_id id) -> comp::Tile&
{
  const auto& [tsEntity, tileset] = singleton<const comp::Tileset>(registry);
  const auto tileEntity = tileset.tiles.at(id);
  return registry.get<comp::Tile>(tileEntity);
}

}  // namespace wanderer::sys
