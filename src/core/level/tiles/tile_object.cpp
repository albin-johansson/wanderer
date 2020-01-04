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
  centerY = get_y() + (get_height() / 2.0f);
  uniqueId = RandomUtils::GetRand();
  hitbox.SetX(get_x());
  hitbox.SetY(get_y());
}

TileObject::~TileObject() noexcept = default;

void TileObject::tick(IWandererCore&, float /*delta*/) {
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

  hitbox.SetX(get_x());
  hitbox.SetY(get_y());
}

float TileObject::get_x() const noexcept {
  return position.x;
}

float TileObject::get_y() const noexcept {
  return position.y;
}

float TileObject::GetCenterY() const noexcept {
  return centerY;
}

float TileObject::get_width() const noexcept {
  return tileSize;
}

float TileObject::get_height() const noexcept {
  return tileSize;
}

const Hitbox& TileObject::get_hitbox() const noexcept {
  return hitbox;
}

int TileObject::GetDepth() const noexcept {
  return depth;
}

void TileObject::add_hitbox(const FRectangle& rectangle, const Vector2& offset) {
  hitbox.AddRectangle(rectangle, offset);
}

uint64_t TileObject::get_unique_id() const noexcept {
  return uniqueId;
}

void TileObject::set_blocked(bool blocked) noexcept {
  hitbox.SetEnabled(blocked);
}

}
