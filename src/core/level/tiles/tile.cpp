#include "tile.h"
#include "objects.h"

namespace albinjohansson::wanderer {

Tile::Tile(TileProperties properties) : properties(std::move(properties)) {}

Tile::~Tile() = default;

void Tile::Tick(ILevel& level) {
  properties.animation.Update();
}

void Tile::Draw(TilePos pos,
                Renderer& renderer,
                const Viewport& viewport,
                const Rectangle& src) const {
  if (GetId() == 0) {
    return;
  }

  Rectangle dst = {viewport.GetTranslatedX(pos.col * SIZE),
                   viewport.GetTranslatedY(pos.row * SIZE),
                   SIZE,
                   SIZE};

  renderer.RenderTexture(*properties.sheet, src, dst);

}

}
