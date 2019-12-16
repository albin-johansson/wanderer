#include "tile_object.h"
#include "tile_set.h"
#include "renderer.h"
#include "viewport.h"
#include "wanderer_core.h"
#include "objects.h"

namespace albinjohansson::wanderer {

TileObject::TileObject(TileID id, const Vector2& position, const std::shared_ptr<TileSet>& tileSet)
    : id(id), position(position) {
  this->tileSet = Objects::RequireNonNull(tileSet);
  centerY = GetY() + (GetHeight() / 2.0f);
  hitbox.AddRectangle(Rectangle(position.x, position.y, Tile::SIZE, Tile::SIZE));
}

TileObject::~TileObject() noexcept = default;

void TileObject::Tick(IWandererCore& core, float delta) {
  tileSet->Tick(id);
}

void TileObject::Draw(Renderer& renderer, const Viewport& viewport) const {
  tileSet->GetTile(id).Draw(position, renderer, viewport, *tileSet);
}

void TileObject::SetDepth(int depth) noexcept {
  if (depth < RenderDepth::MIN) { depth = RenderDepth::MIN; }
  if (depth > RenderDepth::MAX) { depth = RenderDepth::MAX; }
  this->depth = depth;
}

float TileObject::GetX() const noexcept {
  return position.x;
}

float TileObject::GetY() const noexcept {
  return position.y;
}

float TileObject::GetCenterY() const noexcept {
  return centerY;
}

float TileObject::GetWidth() const noexcept {
  return Tile::SIZE;
}

float TileObject::GetHeight() const noexcept {
  return Tile::SIZE;
}

const Hitbox& TileObject::GetHitbox() const noexcept {
  return hitbox;
}

int TileObject::GetDepth() const noexcept {
  return depth;
}

void TileObject::AddHitbox(const Rectangle& rectangle) {
  hitbox.AddRectangle(rectangle);
}

}
