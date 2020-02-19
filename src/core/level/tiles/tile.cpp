#include "tile.h"

#include "game_constants.h"
#include "tile_set.h"

using namespace centurion;
using namespace centurion::video;
using namespace centurion::math;

namespace albinjohansson::wanderer {

Tile::Tile() = default;

Tile::~Tile() = default;

void Tile::tick()
{
  if (isAnimated) {
    animation.update();
  }
}

void Tile::draw(const Vector2& pos,
                const Renderer& renderer,
                const TileSet& tileSet) const
{
  if (get_id() != EMPTY) {
    const auto& src =
        is_animated() ? tileSet.get_tile(get_frame_id()).get_source() : source;
    FRect dst{pos.x, pos.y, GameConstants::tile_size, GameConstants::tile_size};
    renderer.render_tf(*sheet, src, dst);
  }
}

void Tile::set_depth(int depth) noexcept
{
  if (depth < RenderDepth::min) {
    depth = RenderDepth::min;
  }
  if (depth > RenderDepth::max) {
    depth = RenderDepth::max;
  }
  this->depth = depth;
}

TileID Tile::get_frame_id() const
{
  return isAnimated ? animation.get_frame().frameId : id;
}

}  // namespace albinjohansson::wanderer
