#include "tile_rendering_system.hpp"

#include "animated_tile.hpp"
#include "game_constants.hpp"

namespace wanderer::sys {

void render_tile(cen::renderer& renderer,
                 const comp::tile& tile,
                 const int row,
                 const int col) noexcept
{
  const auto x = static_cast<float>(col) * glob::tileWidth<>;
  const auto y = static_cast<float>(row) * glob::tileHeight<>;
  const cen::frect dst{{x, y}, glob::tileSize<cen::farea>};
  renderer.render_t(*tile.sheet, tile.src, dst);
}

auto get_animated_tile(const entt::registry& registry,
                       const comp::tile::entity tileEntity,
                       const comp::tileset& tileset) -> const comp::tile&
{
  assert(registry.has<comp::animated_tile>(tileEntity));

  const auto& animatedTile = registry.get<comp::animated_tile>(tileEntity);
  const auto tileId = animatedTile.frames.at(animatedTile.index).tile;
  const auto animatedEntity = tileset.tiles.at(tileId);

  return registry.get<comp::tile>(animatedEntity);
}

}  // namespace wanderer::sys
