#include "tile_system.hpp"

#include "components/tileset.hpp"
#include "core/ecs/registry_utils.hpp"

namespace wanderer::sys {

auto GetTile(entt::registry& registry, TileID id) -> comp::Tile&
{
  const auto& [tsEntity, tileset] = singleton<const comp::Tileset>(registry);
  const auto tileEntity = tileset.tiles.at(id);
  return registry.get<comp::Tile>(tileEntity);
}

}  // namespace wanderer::sys
