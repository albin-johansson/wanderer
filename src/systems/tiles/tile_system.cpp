#include "tile_system.hpp"

#include "components/tileset.hpp"
#include "core/ecs/registry_utils.hpp"

namespace wanderer::sys {

auto get_tile(entt::registry& registry, const tile_id id) -> comp::tile&
{
  const auto& [tsEntity, tileset] = singleton<const comp::tileset>(registry);
  const auto tileEntity = tileset.tiles.at(id);
  return registry.get<comp::tile>(tileEntity);
}

}  // namespace wanderer::sys
