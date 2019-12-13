#include "tile.h"
#include "vector_2.h"
#include "renderer.h"
#include "viewport.h"
#include "tile_set.h"
#include "rectangle.h"
#include <utility>

namespace albinjohansson::wanderer {

Tile::Tile() noexcept = default;

Tile::~Tile() noexcept = default;

void Tile::Tick() {
  if (isAnimated) {
    animation.Update();
  }
}

void Tile::Draw(const Vector2& pos,
                Renderer& renderer,
                const Viewport& viewport,
                const TileSet& tileSet) const {
  if (GetId() != EMPTY) {
    const auto& src = IsAnimated() ? tileSet.GetTile(GetFrameId()).GetSource() : source;
    Rectangle dst = {viewport.GetTranslatedX(pos.x), viewport.GetTranslatedY(pos.y), SIZE, SIZE};
    renderer.RenderTexture(*sheet, src, dst);

    if (IsBlocked()) {
      renderer.SetColor(0xFF, 0, 0);
      renderer.RenderRect(dst.GetX() + hitbox.GetX(),
                          dst.GetY() + hitbox.GetY(),
                          hitbox.GetWidth(),
                          hitbox.GetHeight());
    }
  }
}

void Tile::SetSheet(std::shared_ptr<Image> sheet) {
  this->sheet = std::move(sheet);
}

void Tile::SetBlocked(bool isBlocked) noexcept {
  this->isBlocked = isBlocked;
}

void Tile::SetAnimated(bool isAnimated) noexcept {
  this->isAnimated = isAnimated;
}

void Tile::SetObject(bool isObject) noexcept {
  this->isObject = isObject;
}

void Tile::SetDepth(int depth) noexcept {
  if (depth < RenderDepth::MIN) { depth = RenderDepth::MIN; }
  if (depth > RenderDepth::MAX) { depth = RenderDepth::MAX; }
  this->depth = depth;
}

void Tile::SetId(TileID id) noexcept {
  this->id = id;
}

void Tile::SetAnimation(const TileAnimation& animation) noexcept {
  this->animation = animation;
}

void Tile::SetHitbox(const Rectangle& hitbox) noexcept {
  this->hitbox = hitbox;
}

void Tile::SetSource(const Rectangle& source) noexcept {
  this->source = source;
}

Image& Tile::GetImage() const noexcept {
  return *sheet;
}

TileID Tile::GetId() const noexcept {
  return id;
}

int Tile::GetDepth() const noexcept {
  return depth;
}

bool Tile::IsObject() const noexcept {
  return isObject;
}

bool Tile::IsBlocked() const noexcept {
  return isBlocked;
}

bool Tile::IsAnimated() const noexcept {
  return isAnimated;
}

TileID Tile::GetFrameId() const {
  return isAnimated ? animation.GetFrame().frameId : id;
}

const Rectangle& Tile::GetSource() const noexcept {
  return source;
}

}
