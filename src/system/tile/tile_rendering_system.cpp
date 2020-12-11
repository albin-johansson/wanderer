#include "tile_rendering_system.hpp"

#include "animated_tile.hpp"
#include "game_constants.hpp"

namespace wanderer::sys::tile {
namespace {

inline constexpr cen::farea g_dstSize{g_tileSize<float>, g_tileSize<float>};

}

void render(cen::renderer& renderer,
            const comp::tile& tile,
            const int row,
            const int col) noexcept
{
  const auto x = static_cast<float>(col) * g_tileSize<float>;
  const auto y = static_cast<float>(row) * g_tileSize<float>;
  const cen::frect dst{{x, y}, g_dstSize};
  renderer.render_t(*tile.sheet, tile.src, dst);
}

auto animated_tile(const entt::registry& registry,
                   const comp::tile::entity tileEntity,
                   const comp::tileset& tileset) -> const comp::tile&
{
  assert(registry.has<comp::animated_tile>(tileEntity));

  const auto& animatedTile = registry.get<comp::animated_tile>(tileEntity);
  const auto tileId = animatedTile.frames.at(animatedTile.index).tile;
  const auto animatedEntity = tileset.tiles.at(tileId);

  return registry.get<comp::tile>(animatedEntity);
}

}  // namespace wanderer::sys::tile
