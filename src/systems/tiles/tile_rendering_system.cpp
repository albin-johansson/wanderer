#include "tile_rendering_system.hpp"

#include <cassert>        // assert
#include <centurion.hpp>  // farea, frect

#include "components/gfx/tile_animation.hpp"
#include "core/game_constants.hpp"

namespace wanderer::sys {

void render_tile(graphics_context& graphics,
                 const comp::tile& tile,
                 const grid_position position) noexcept
{
  const auto dst = cen::rect(position.col * glob::tile_width<float>,
                             position.row * glob::tile_height<float>,
                             glob::tile_width<float>,
                             glob::tile_height<float>);
  graphics.render(tile.texture, tile.src, dst);
}

auto get_animated_tile(const entt::registry& registry,
                       const entt::entity tile,
                       const comp::tileset& tileset) -> const comp::tile&
{
  assert(registry.all_of<comp::tile_animation>(tile));

  const auto& animation = registry.get<comp::tile_animation>(tile);
  const auto id = animation.frames.at(animation.index).tile;

  return registry.get<comp::tile>(tileset.tiles.at(id));
}

}  // namespace wanderer::sys
