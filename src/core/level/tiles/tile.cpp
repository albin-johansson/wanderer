#include "tile.h"
#include <utility>

namespace albinjohansson::wanderer {

Tile::Tile(TileProperties properties) : properties(std::move(properties)) {}

Tile::~Tile() = default;

void Tile::Tick() {
  if (properties.animated) {
    properties.animation.Update();
  }
}

void Tile::Draw(TilePos pos,
                Renderer& renderer,
                const Viewport& viewport,
                const Rectangle& src) const {
  if (GetId() == EMPTY) {
    return;
  }

  Rectangle dst = {viewport.GetTranslatedX(pos.col * SIZE),
                   viewport.GetTranslatedY(pos.row * SIZE),
                   SIZE,
                   SIZE};

  renderer.RenderTexture(*properties.sheet, src, dst);

  if (IsBlocked()) {
    renderer.SetColor(0xFF, 0, 0);
    renderer.RenderRect(dst.GetX() + properties.hitbox.GetX(),
                        dst.GetY() + properties.hitbox.GetY(),
                        properties.hitbox.GetWidth(),
                        properties.hitbox.GetHeight());
  }
}

}
