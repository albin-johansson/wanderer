#include "tile_object.h"
#include "tile_set.h"
#include "renderer.h"
#include "viewport.h"
#include "wanderer_core.h"
#include "require.h"
#include "random_utils.h"
#include "game_constants.h"

namespace albinjohansson::wanderer {

TileObject::TileObject(TileID id, const Vector2& position, const std::shared_ptr<TileSet>& tileSet)
    : position(position), id(id) {
  this->tileSet = Require::NotNull(tileSet);
  centerY = GetY() + (GetHeight() / 2.0f);
  uniqueId = RandomUtils::GetRand();
  hitbox.SetX(GetX());
  hitbox.SetY(GetY());
}

TileObject::~TileObject() noexcept = default;

void TileObject::Tick(IWandererCore&, float /*delta*/) {
  tileSet->Tick(id);
}

void TileObject::Draw(const Renderer& renderer, const Viewport&) const {
  tileSet->GetTile(id).Draw(position, renderer, *tileSet);
}

void TileObject::SetDepth(int depth) noexcept {
  if (depth < RenderDepth::MIN) { depth = RenderDepth::MIN; }
  if (depth > RenderDepth::MAX) { depth = RenderDepth::MAX; }
  this->depth = depth;
}

void TileObject::SetHitbox(const Hitbox& h) noexcept {
  this->hitbox = h;

  hitbox.SetX(GetX());
  hitbox.SetY(GetY());
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
  return TILE_SIZE;
}

float TileObject::GetHeight() const noexcept {
  return TILE_SIZE;
}

const Hitbox& TileObject::GetHitbox() const noexcept {
  return hitbox;
}

int TileObject::GetDepth() const noexcept {
  return depth;
}

void TileObject::AddHitbox(const FRectangle& rectangle, const Vector2& offset) {
  hitbox.AddRectangle(rectangle, offset);
}

uint64_t TileObject::GetUniqueID() const noexcept {
  return uniqueId;
}

void TileObject::SetBlocked(bool blocked) noexcept {
  hitbox.SetEnabled(blocked);
}

}
