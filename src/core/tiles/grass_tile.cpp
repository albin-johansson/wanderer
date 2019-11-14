#include "grass_tile.h"

namespace wanderer::core {

GrassTile::GrassTile(int row, int col, int id) : AbstractTile(row, col, id) {
}

GrassTile::~GrassTile() = default;

void GrassTile::Draw(visuals::Renderer& renderer, const Viewport& viewport) const noexcept {
//  if (image != nullptr) {
//    auto x = viewport.GetTranslatedX(static_cast<float>(GetCol()) * SIZE);
//    auto y = viewport.GetTranslatedY(static_cast<float>(GetRow()) * SIZE);
//    renderer.RenderTexture(image->GetTexture(), x, y, SIZE, SIZE);
//  }
}

}