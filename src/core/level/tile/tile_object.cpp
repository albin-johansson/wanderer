#include "tile_object.h"

#include "game_constants.h"
#include "game_object_id.h"
#include "require.h"
#include "tile_set.h"
#include "viewport.h"
#include "wanderer_core.h"

using namespace centurion;

namespace wanderer {

TileObject::TileObject(TileID id,
                       const Vector2& position,
                       const SharedPtr<TileSet>& tileSet)
    : m_position{position}, m_id{id}
{
  this->m_tileSet = Require::not_null(tileSet);
  m_centerY = get_y() + (get_height() / 2.0f);
  m_uniqueId = GameObjectID::next();
  m_hitbox.set_x(get_x());
  m_hitbox.set_y(get_y());
}

TileObject::~TileObject() noexcept = default;

void TileObject::tick(IWandererCore&, float /*delta*/)
{
  m_tileSet->tick(m_id);
}

void TileObject::draw(Renderer& renderer, const Viewport&) const
{
  m_tileSet->get_tile(m_id).draw(m_position, renderer, *m_tileSet);
}

void TileObject::SetDepth(int depth) noexcept
{
  if (depth < RenderDepth::min) {
    depth = RenderDepth::min;
  }
  if (depth > RenderDepth::max) {
    depth = RenderDepth::max;
  }
  this->m_depth = depth;
}

void TileObject::SetHitbox(const Hitbox& h) noexcept
{
  this->m_hitbox = h;

  m_hitbox.set_x(get_x());
  m_hitbox.set_y(get_y());
}

float TileObject::get_x() const noexcept
{
  return m_position.x;
}

float TileObject::get_y() const noexcept
{
  return m_position.y;
}

float TileObject::get_center_y() const noexcept
{
  return m_centerY;
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
  return m_hitbox;
}

int TileObject::get_depth() const noexcept
{
  return m_depth;
}

void TileObject::add_hitbox(const FRect& rectangle, const Vector2& offset)
{
  m_hitbox.add_rectangle(rectangle, offset);
}

uint64 TileObject::get_unique_id() const noexcept
{
  return m_uniqueId;
}

void TileObject::set_blocked(bool blocked) noexcept
{
  m_hitbox.set_enabled(blocked);
}

}  // namespace wanderer
