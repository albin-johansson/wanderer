#include "tile_rendering_system.hpp"

#include "component/animated_tile.hpp"
#include "game_constants.hpp"

namespace wanderer::sys::tile {
namespace {

inline constexpr cen::farea dstSize{g_tileSize<float>, g_tileSize<float>};

}

void render(cen::renderer& renderer,
            const comp::tile& tile,
            const int row,
            const int col) noexcept
{
  const auto x = static_cast<float>(col) * g_tileSize<float>;
  const auto y = static_cast<float>(row) * g_tileSize<float>;
  const cen::frect dst{{x, y}, dstSize};
  renderer.render_t(*tile.sheet, tile.src, dst);
}

auto animated_tile(entt::registry& registry,
                   const comp::tile::entity tileEntity,
                   const comp::tileset& tileset) -> const comp::tile&
{
  assert(registry.has<comp::animated_tile>(tileEntity.get()));

  const auto& animatedTile =
      registry.get<comp::animated_tile>(tileEntity.get());

  const tile_id id = animatedTile.frames.at(animatedTile.index).tile;
  const comp::tile::entity animated = tileset.tiles.at(id);

  return registry.get<comp::tile>(animated.get());
}

}  // namespace wanderer::sys::tile
