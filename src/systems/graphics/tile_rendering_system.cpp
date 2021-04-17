#include "tile_rendering_system.hpp"

#include <centurion.hpp>  // farea, frect

#include "components/graphics/tile_animation.hpp"
#include "core/game_constants.hpp"

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
                       const ctx::tileset& tileset) -> const comp::tile&
{
  assert(registry.all_of<comp::tile_animation>(tileEntity));

  const auto& animation = registry.get<comp::tile_animation>(tileEntity);
  const auto tileId = animation.frames.at(animation.index).tile;

  return registry.get<comp::tile>(tileset.tiles.at(tileId));
}

}  // namespace wanderer::sys
