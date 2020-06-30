#include "tile_rendering_system.h"

#include "animated_tile.h"
#include "game_constants.h"

namespace wanderer::system::tile {
namespace {

inline constexpr ctn::FArea dstSize{g_tileSize<float>, g_tileSize<float>};

}

void render(ctn::Renderer& renderer,
            const Tile& tile,
            const int row,
            const int col) noexcept
{
  const auto x = static_cast<float>(col) * g_tileSize<float>;
  const auto y = static_cast<float>(row) * g_tileSize<float>;
  const ctn::FRect dst{{x, y}, dstSize};
  renderer.render_tf(*tile.sheet, tile.src, dst);
}

auto animated_tile(entt::registry& registry,
                   const TileEntity tileEntity,
                   const Tileset& tileset) -> const Tile&
{
  assert(registry.has<AnimatedTile>(tileEntity.get()));

  const auto& animatedTile = registry.get<AnimatedTile>(tileEntity.get());

  const TileID id = animatedTile.frames.at(animatedTile.frame).tile;
  const TileEntity animated = tileset.tiles.at(id);

  return registry.get<Tile>(animated.get());
}

}  // namespace wanderer::system::tile
