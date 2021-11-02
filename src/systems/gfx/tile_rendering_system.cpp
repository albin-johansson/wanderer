#include "tile_rendering_system.hpp"

#include <cassert>  // assert

#include <centurion.hpp>  // farea, frect

#include "components/tile_animation.hpp"
#include "core/game_constants.hpp"

namespace wanderer::sys {

void RenderTile(GraphicsContext& graphics,
                const Tile& tile,
                GridPosition position) noexcept
{
  const auto dst = cen::rect(position.col * glob::tile_width<float>,
                             position.row * glob::tile_height<float>,
                             glob::tile_width<float>,
                             glob::tile_height<float>);
  graphics.Render(tile.texture, tile.src, dst);
}

auto GetAnimatedTile(const entt::registry& registry,
                     entt::entity tile,
                     const Tileset& tileset) -> const Tile&
{
  assert(registry.all_of<TileAnimation>(tile));

  const auto& animation = registry.get<TileAnimation>(tile);
  const auto id = animation.frames.at(animation.index).tile;

  return registry.get<Tile>(tileset.tiles.at(id));
}

}  // namespace wanderer::sys
