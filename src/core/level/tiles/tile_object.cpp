#include "tile_object.h"
#include "tile_set.h"
#include "renderer.h"
#include "viewport.h"
#include "wanderer_core.h"
#include "objects.h"
#include <utility>

namespace albinjohansson::wanderer {

TileObject::TileObject(TileID id, const Vector2& position, std::shared_ptr<TileSet> tileSet)
    : id(id), position(position) {
  this->tileSet = Objects::RequireNonNull(std::move(tileSet));
  centerY = GetY() + (GetHeight() / 2.0f);
}

TileObject::~TileObject() noexcept = default;

void TileObject::Tick(IWandererCore& core, float delta) {
  tileSet->Tick(id);
}

void TileObject::Draw(Renderer& renderer, const Viewport& viewport) const {
  const auto& tile = tileSet->GetTile(id);
  tile.Draw(position, renderer, viewport, *tileSet);

  renderer.SetColor(0xff, 0, 0);
  renderer.RenderFillRect(viewport.GetTranslatedX(GetX() + (Tile::SIZE / 2.0f) - 2),
                          viewport.GetTranslatedY(centerY - 2),
                          5.0f,
                          5.0f);
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

Rectangle TileObject::GetHitbox() const noexcept {
  return Rectangle(position.x, position.y, Tile::SIZE, Tile::SIZE);
}

int TileObject::GetDepth() const noexcept {
  return depth;
}

}
