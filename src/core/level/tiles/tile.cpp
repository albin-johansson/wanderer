#include "tile.h"
#include "vector_2.h"
#include <utility>

namespace albinjohansson::wanderer {

Tile::Tile(TileProperties properties) : properties(std::move(properties)) {}

Tile::~Tile() = default;

void Tile::Tick() {
  if (properties.animated) {
    properties.animation.Update();
  }
}

void Tile::Draw(const Vector2& pos,
                Renderer& renderer,
                const Viewport& viewport,
                const Rectangle& src) const {
  if (GetId() == EMPTY) {
    return;
  }

  Rectangle dst = {viewport.GetTranslatedX(pos.x),
                   viewport.GetTranslatedY(pos.y),
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

bool Tile::HasGroup() const noexcept {
  return properties.group != 0;
}

bool Tile::IsPivot() const noexcept {
  return properties.isPivot;
}

int Tile::GetGroup() const noexcept {
  return properties.group;
}

int Tile::GetRenderGroup() const noexcept {
  return properties.renderGroup;
}

}
