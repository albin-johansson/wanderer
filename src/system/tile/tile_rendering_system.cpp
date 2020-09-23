#include "tile_rendering_system.hpp"

#include "animated_tile.hpp"
#include "game_constants.hpp"

namespace wanderer::sys::tile {
namespace {

inline constexpr cen::farea dstSize{g_tileSize<float>, g_tileSize<float>};

}

void render(cen::renderer& renderer,
            const comp::Tile& tile,
            const int row,
            const int col) noexcept
{
  const auto x = static_cast<float>(col) * g_tileSize<float>;
  const auto y = static_cast<float>(row) * g_tileSize<float>;
  const cen::frect dst{{x, y}, dstSize};
  renderer.render_t(*tile.sheet, tile.src, dst);
}

auto animated_tile(entt::registry& registry,
                   const comp::Tile::entity tileEntity,
                   const comp::tileset& tileset) -> const comp::Tile&
{
  assert(registry.has<comp::AnimatedTile>(tileEntity.get()));

  const auto& animatedTile = registry.get<comp::AnimatedTile>(tileEntity.get());

  const tile_id id = animatedTile.frames.at(animatedTile.frame).tile;
  const comp::Tile::entity animated = tileset.tiles.at(id);

  return registry.get<comp::Tile>(animated.get());
}

}  // namespace wanderer::sys::tile
