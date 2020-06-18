#include "tile_rendering_system.h"

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

}  // namespace wanderer::system::tile
