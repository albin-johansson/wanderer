#include "drawable_tile.h"

namespace albinjohansson::wanderer {

DrawableTile::DrawableTile(float x, float y, TileID id, TileSet_wptr tileSet)
    : x(x), y(y), id(id) {
  this->tileSet = std::move(tileSet);
}

DrawableTile::~DrawableTile() = default;

void DrawableTile::Draw(Renderer& renderer, const Viewport& viewport) const {
  if (id == Tile::EMPTY) {
    return;
  }

  auto ts = tileSet.lock();
  if (ts) {
    const TilePos pos = {static_cast<int>(y / Tile::SIZE), static_cast<int>(x / Tile::SIZE)};
    const auto& tile = ts->GetTile(id);
    tile.Draw(pos, renderer, viewport, ts->GetSource(tile.GetFrameId()));
  }
}

float DrawableTile::GetX() const noexcept {
  return x;
}

float DrawableTile::GetY() const noexcept {
  return y;
}

}