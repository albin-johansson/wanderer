#include "tile.h"
#include "renderer.h"
#include "tile_set.h"
#include "rectangle.h"
#include "game_constants.h"

namespace albinjohansson::wanderer {

Tile::Tile() = default;

Tile::~Tile() = default;

void Tile::Tick() {
  if (isAnimated) {
    animation.Update();
  }
}

void Tile::Draw(const Vector2& pos,
                const Renderer& renderer,
                const TileSet& tileSet) const {
  if (GetId() != EMPTY) {
    const auto& src = IsAnimated() ? tileSet.GetTile(GetFrameId()).GetSource()
                                   : source;
    FRectangle dst{pos.x, pos.y, Area{tileSize, tileSize}};
    renderer.RenderTextureTranslated(*sheet, src, dst);
  }
}

void Tile::SetSheet(const std::shared_ptr<Image>& sheet) {
  this->sheet = sheet;
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

void Tile::SetHitbox(const Hitbox& hitbox) noexcept {
  this->hitbox = hitbox;
}

void Tile::SetSource(const Rectangle& source) noexcept {
  this->source = source;
}

void Tile::AddRectangle(const FRectangle& rect, const Vector2& offset) {
  hitbox.AddRectangle(rect, offset);
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

const Hitbox& Tile::GetHitbox() const noexcept {
  return hitbox;
}

}
