#include "tile.h"
#include "vector_2.h"
#include "viewport.h"
#include "renderer.h"
#include "tile_set.h"
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
                const TileSet& tileSet) const {
  if (GetId() == EMPTY) {
    return;
  }

  Rectangle src = IsAnimated() ? tileSet.GetSource(GetFrameId())
                               : tileSet.GetSource(GetId());

  // TODO this could be pre-computed
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

int Tile::GetDepth() const noexcept {
  return properties.depth;
}

bool Tile::IsObject() const noexcept {
  return properties.isObject;
}

TileID Tile::GetFrameId() const {
  return properties.animated ? properties.animation.GetFrame().frameId : properties.id;
}

}
