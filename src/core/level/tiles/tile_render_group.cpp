#include "tile_render_group.h"

namespace albinjohansson::wanderer {

TileRenderGroup::TileRenderGroup(float pivotX, float pivotY, std::vector<DrawableTile_sptr> tiles)
    : pivotX(pivotX), pivotY(pivotY), tiles(std::move(tiles)) {}

TileRenderGroup::TileRenderGroup(float pivotX,
                                 float pivotY,
                                 std::vector<DrawableTile_sptr>&& tiles)
    : pivotX(pivotX), pivotY(pivotY), tiles(tiles) {}

TileRenderGroup::~TileRenderGroup() = default;

void TileRenderGroup::Draw(Renderer& renderer, const Viewport& viewport) const {
  for (const auto& tile : tiles) {
    tile->Draw(renderer, viewport);
  }

  // FIXME pivots are not working
  const auto x = viewport.GetTranslatedX(pivotX);
  const auto y = viewport.GetTranslatedY(pivotY);

  renderer.SetColor(0xff, 0, 0);
  renderer.RenderFillRect(x - 5, y - 5, 10.0f, 10.0f);
}

float TileRenderGroup::GetX() const noexcept {
  return pivotX;
}

float TileRenderGroup::GetY() const noexcept {
  return pivotY;
}

}
