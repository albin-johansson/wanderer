#include "tile_rendering_system.h"

#include "animated_tile.h"
#include "game_constants.h"

using centurion::FArea;
using centurion::FRect;
using centurion::Renderer;

namespace wanderer::system::tile {
namespace {

inline constexpr FArea dstSize{g_tileSize<float>, g_tileSize<float>};

}

void render(Renderer& renderer,
            const Tile& tile,
            const int row,
            const int col) noexcept
{
  const auto x = static_cast<float>(col) * g_tileSize<float>;
  const auto y = static_cast<float>(row) * g_tileSize<float>;
  const FRect dst{{x, y}, dstSize};
  renderer.render_tf(*tile.sheet, tile.src, dst);
}

auto animated_tile(entt::registry& registry,
                   const entt::entity tileEntity,
                   const Tileset& tileset) -> const Tile&
{
  assert(registry.has<AnimatedTile>(tileEntity));

  const auto& animatedTile = registry.get<AnimatedTile>(tileEntity);

  const auto id = animatedTile.frames.at(animatedTile.frame).tile;
  const auto animatedTileEntity = tileset.tiles.at(id);

  return registry.get<Tile>(animatedTileEntity);
}

}  // namespace wanderer::system::tile
