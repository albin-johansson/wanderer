#include "tile_rendering_system.hpp"

#include "animated_tile.hpp"
#include "game_constants.hpp"

namespace wanderer::sys {

void render_tile(graphics_context& graphics,
                 const comp::tile& tile,
                 const int row,
                 const int col) noexcept
{
  const auto x = static_cast<float>(col) * glob::tile_width<>;
  const auto y = static_cast<float>(row) * glob::tile_height<>;
  const cen::frect dst{{x, y}, glob::tile_size<cen::farea>};

  graphics.render(tile.texture, tile.src, dst);
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
