#include "tile.h"

#include "game_constants.h"
#include "tile_set.h"

using namespace centurion;

namespace wanderer {

Tile::Tile() = default;

Tile::~Tile() = default;

void Tile::tick()
{
  if (m_isAnimated) {
    m_animation.update();
  }
}

void Tile::draw(const Vector2& pos,
                Renderer& renderer,
                const TileSet& tileSet) const
{
  if (get_id() != empty) {
    const auto& src = is_animated()
                          ? tileSet.get_tile(get_frame_id()).get_source()
                          : m_source;
    FRect dst{pos.x, pos.y, GameConstants::tile_size, GameConstants::tile_size};
    renderer.render_tf(*m_sheet, src, dst);
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
  this->m_depth = depth;
}

TileID Tile::get_frame_id() const
{
  return m_isAnimated ? m_animation.get_frame().frameId : m_id;
}

}  // namespace wanderer
