#include "tile_object.h"

#include "game_constants.h"
#include "game_object_id.h"
#include "require.h"
#include "tile_set.h"
#include "viewport.h"
#include "wanderer_core.h"

using namespace centurion;

namespace albinjohansson::wanderer {

TileObject::TileObject(TileID id,
                       const Vector2& position,
                       const Shared<TileSet>& tileSet)
    : position{position}, id{id}
{
  this->tileSet = Require::not_null(tileSet);
  centerY = get_y() + (get_height() / 2.0f);
  uniqueId = GameObjectID::next();
  hitbox.set_x(get_x());
  hitbox.set_y(get_y());
}

TileObject::~TileObject() noexcept = default;

void TileObject::tick(IWandererCore&, float /*delta*/)
{
  tileSet->tick(id);
}

void TileObject::draw(Renderer& renderer, const Viewport&) const
{
  tileSet->get_tile(id).draw(position, renderer, *tileSet);
}

void TileObject::SetDepth(int depth) noexcept
{
  if (depth < RenderDepth::min) {
    depth = RenderDepth::min;
  }
  if (depth > RenderDepth::max) {
    depth = RenderDepth::max;
  }
  this->depth = depth;
}

void TileObject::SetHitbox(const Hitbox& h) noexcept
{
  this->hitbox = h;

  hitbox.set_x(get_x());
  hitbox.set_y(get_y());
}

float TileObject::get_x() const noexcept
{
  return position.x;
}

float TileObject::get_y() const noexcept
{
  return position.y;
}

float TileObject::get_center_y() const noexcept
{
  return centerY;
}

float TileObject::get_width() const noexcept
{
  return GameConstants::tile_size;
}

float TileObject::get_height() const noexcept
{
  return GameConstants::tile_size;
}

const Hitbox& TileObject::get_hitbox() const noexcept
{
  return hitbox;
}

int TileObject::get_depth() const noexcept
{
  return depth;
}

void TileObject::add_hitbox(const FRect& rectangle, const Vector2& offset)
{
  hitbox.add_rectangle(rectangle, offset);
}

uint64 TileObject::get_unique_id() const noexcept
{
  return uniqueId;
}

void TileObject::set_blocked(bool blocked) noexcept
{
  hitbox.set_enabled(blocked);
}

}  // namespace albinjohansson::wanderer
