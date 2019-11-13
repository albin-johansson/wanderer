#include "grass_tile.h"

namespace wanderer::core {

GrassTile::GrassTile(int row, int col, int id) : AbstractTile(row, col, id) {
  texture = nullptr; // TODO...
}

GrassTile::~GrassTile() = default;

void GrassTile::Draw(visuals::Renderer& renderer, const Viewport& viewport) const noexcept {
  auto x = viewport.GetTranslatedX(static_cast<float>(GetCol()) * SIZE);
  auto y = viewport.GetTranslatedY(static_cast<float>(GetRow()) * SIZE);

  renderer.SetColor(0x72, 0x9E, 0x74);
  renderer.RenderFillRect(x, y, SIZE, SIZE);
  renderer.SetColor(0, 0, 0);
  renderer.RenderRect(x, y, SIZE, SIZE);
}

}