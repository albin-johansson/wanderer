#include "drawable_tile.h"
#include "bad_state_exception.h"

namespace albinjohansson::wanderer {

DrawableTile::DrawableTile(float x, float y, TileID id, TileSet_wptr tileSet)
    : position(x, y), id(id) {
  if (id == Tile::EMPTY) {
    throw BadStateException("Attempted to create drawable tile with Tile::EMPTY!");
  }
  this->tileSet = std::move(tileSet);
}

DrawableTile::~DrawableTile() = default;

void DrawableTile::Draw(Renderer& renderer, const Viewport& viewport) const {
  const auto ts = tileSet.lock();
  if (ts) {
    const auto& tile = ts->GetTile(id);
    tile.Draw(position, renderer, viewport, *ts);
  }
}

float DrawableTile::GetCenterY() const noexcept {
  return position.y + (Tile::SIZE / 2.0f); // FIXME the offset is constexpr
}

}