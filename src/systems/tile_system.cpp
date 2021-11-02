#include "tile_system.hpp"

#include "components/tileset.hpp"
#include "core/ecs/registry_utils.hpp"

namespace wanderer::sys {

auto GetTile(entt::registry& registry, TileID id) -> Tile&
{
  const auto& [tsEntity, tileset] = singleton<const Tileset>(registry);
  const auto tileEntity = tileset.tiles.at(id);
  return registry.get<Tile>(tileEntity);
}

}  // namespace wanderer::sys
