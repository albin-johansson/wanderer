#include "drawable_tile.h"

namespace albinjohansson::wanderer {

DrawableTile::DrawableTile(float x, float y, TileID id, TileSet_wptr tileSet)
    : position(x, y), id(id) {
  this->tileSet = std::move(tileSet);
}

DrawableTile::~DrawableTile() = default;

void DrawableTile::Draw(Renderer& renderer, const Viewport& viewport) const {
  if (id == Tile::EMPTY) {
    return;
  }

  const auto ts = tileSet.lock();
  if (ts) {
    const auto& tile = ts->GetTile(id);
    const auto srcRectId = (tile.IsAnimated()) ? tile.GetFrameId() : id;
    tile.Draw(position, renderer, viewport, ts->GetSource(srcRectId));

    renderer.SetColor(0, 0, 0);
    renderer.RenderRect(viewport.GetTranslatedX(position.x),
                        viewport.GetTranslatedY(position.y),
                        Tile::SIZE,
                        Tile::SIZE);
  }
}

float DrawableTile::GetX() const noexcept {
  return position.x;
}

float DrawableTile::GetY() const noexcept {
  return position.y;
}

}