#include "tile.h"
#include "renderer.h"
#include "tile_set.h"
#include "rectangle.h"
#include "game_constants.h"
#include "image.h"

using namespace centurion;

namespace albinjohansson::wanderer {

Tile::Tile() = default;

Tile::~Tile() = default;

void Tile::tick() {
  if (isAnimated) {
    animation.update();
  }
}

void Tile::draw(const Vector2& pos, const Renderer& renderer, const TileSet& tileSet) const {
  if (get_id() != EMPTY) {
    const auto& src = is_animated() ? tileSet.GetTile(get_frame_id()).get_source()
                                    : source;
    FRectangle dst{pos.x, pos.y, Area{tileSize, tileSize}};
    renderer.draw_image_translated(*sheet, src, dst);
  }
}

void Tile::set_depth(int depth) noexcept {
  if (depth < RenderDepth::min) { depth = RenderDepth::min; }
  if (depth > RenderDepth::max) { depth = RenderDepth::max; }
  this->depth = depth;
}

TileID Tile::get_frame_id() const {
  return isAnimated ? animation.get_frame().frameId : id;
}

}
