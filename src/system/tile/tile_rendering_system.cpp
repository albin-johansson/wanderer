#include "tile_rendering_system.hpp"

#include "animated_tile.hpp"
#include "game_constants.hpp"

using namespace wanderer::comp;

namespace wanderer::sys::tile {
namespace {

inline constexpr cen::farea dstSize{g_tileSize<float>, g_tileSize<float>};

}

void render(cen::renderer& renderer,
            const Tile& tile,
            const int row,
            const int col) noexcept
{
  const auto x = static_cast<float>(col) * g_tileSize<float>;
  const auto y = static_cast<float>(row) * g_tileSize<float>;
  const cen::frect dst{{x, y}, dstSize};
  renderer.render_t(*tile.sheet, tile.src, dst);
}

auto animated_tile(entt::registry& registry,
                   const Tile::entity tileEntity,
                   const Tileset& tileset) -> const Tile&
{
  assert(registry.has<AnimatedTile>(tileEntity.get()));

  const auto& animatedTile = registry.get<AnimatedTile>(tileEntity.get());

  const tile_id id = animatedTile.frames.at(animatedTile.frame).tile;
  const Tile::entity animated = tileset.tiles.at(id);

  return registry.get<Tile>(animated.get());
}

}  // namespace wanderer::sys::tile
