#include "movable_delegate.h"

#include <rect.h>

#include <stdexcept>

#include "game_object.h"
#include "game_object_id.h"

using namespace centurion;

namespace wanderer {

MovableDelegate::MovableDelegate(int depth, float width, float height)
    : m_depth(depth), m_width(width), m_height(height)
{
  if (width < 1 || height < 1) {
    throw std::invalid_argument("Invalid dimensions!");
  }
  m_uniqueId = GameObjectID::next();
}

MovableDelegate::~MovableDelegate() = default;

void MovableDelegate::draw(Renderer&, const Viewport&) const noexcept
{
  /* do nothing */
}

void MovableDelegate::tick(IWandererCore&, float /*delta*/)
{
  save_position();
  update_position();
  update_direction();
}

void MovableDelegate::save_position() noexcept
{
  m_prevPosition.set(m_currPosition);
}

void MovableDelegate::update_position()
{
  m_hitbox.set_x(m_currPosition.x);
  m_hitbox.set_y(m_currPosition.y);
}

void MovableDelegate::update_direction()
{
  if (m_velocity.x > 0) {
    m_dominantDirection = Direction::Right;
  } else if (m_velocity.x < 0) {
    m_dominantDirection = Direction::Left;
  } else {
    if (m_velocity.y < 0) {
      m_dominantDirection = Direction::Up;
    } else if (m_velocity.y > 0) {
      m_dominantDirection = Direction::Down;
    }
  }
}

void MovableDelegate::move(Direction direction) noexcept
{
  switch (direction) {
    case Direction::Right: {
      m_velocity.x = m_speed;
      break;
    }
    case Direction::Left: {
      m_velocity.x = -m_speed;
      break;
    }
    case Direction::Up: {
      m_velocity.y = -m_speed;
      break;
    }
    case Direction::Down: {
      m_velocity.y = m_speed;
      break;
    }
    default:
      break;
  }
  m_velocity.norm();
  m_velocity.scale(m_speed);
}

void MovableDelegate::stop(Direction direction) noexcept
{
  switch (direction) {
    case Direction::Right:
      [[fallthrough]];
    case Direction::Left: {
      m_velocity.x = 0;
      break;
    }
    case Direction::Up:
      [[fallthrough]];
    case Direction::Down: {
      m_velocity.y = 0;
      break;
    }
    default:
      break;
  }
  m_velocity.norm();
  m_velocity.scale(m_speed);
}

void MovableDelegate::stop() noexcept
{
  m_velocity.zero();
}

void MovableDelegate::interpolate(float alpha) noexcept
{
  m_interpolatedPosition.set(m_currPosition);
  m_interpolatedPosition.interpolate(m_prevPosition, alpha);
}

void MovableDelegate::set_speed(float speed) noexcept
{
  this->m_speed = speed;
  m_velocity.norm();
  m_velocity.scale(speed);
}

void MovableDelegate::add_x(float dx) noexcept
{
  m_currPosition.add(dx, 0);
  update_position();
}

void MovableDelegate::add_y(float dy) noexcept
{
  m_currPosition.add(0, dy);
  update_position();
}

void MovableDelegate::set_x(float x) noexcept
{
  m_currPosition.x = x;
  update_position();
}

void MovableDelegate::set_y(float y) noexcept
{
  m_currPosition.y = y;
  update_position();
}

void MovableDelegate::set_velocity(const Vector2& v) noexcept
{
  m_velocity.set(v);
}

void MovableDelegate::add_hitbox(const FRect& rectangle, const Vector2& offset)
{
  m_hitbox.add_rectangle(rectangle, offset);
  update_position();
}

void MovableDelegate::set_blocked(bool blocked) noexcept
{
  m_hitbox.set_enabled(blocked);
}

int MovableDelegate::get_depth() const noexcept
{
  return m_depth;
}

float MovableDelegate::get_center_y() const noexcept
{
  return m_currPosition.y + (m_height / 2.0f);
}

float MovableDelegate::get_speed() const noexcept
{
  return m_speed;
}

float MovableDelegate::get_width() const noexcept
{
  return m_width;
}

float MovableDelegate::get_height() const noexcept
{
  return m_height;
}

float MovableDelegate::get_x() const noexcept
{
  return m_currPosition.x;
}

float MovableDelegate::get_y() const noexcept
{
  return m_currPosition.y;
}

const Hitbox& MovableDelegate::get_hitbox() const noexcept
{
  return m_hitbox;
}

Direction MovableDelegate::get_dominant_direction() const noexcept
{
  return m_dominantDirection;
}

const Vector2& MovableDelegate::get_velocity() const noexcept
{
  return m_velocity;
}

const Vector2& MovableDelegate::get_position() const noexcept
{
  return m_currPosition;
}

const Vector2& MovableDelegate::get_interpolated_position() const noexcept
{
  return m_interpolatedPosition;
}

const Vector2& MovableDelegate::get_previous_position() const noexcept
{
  return m_prevPosition;
}

bool MovableDelegate::will_intersect(const IGameObject* other,
                                     float delta) const
{
  return other &&
         m_hitbox.will_intersect(other->get_hitbox(), get_next_position(delta));
}

uint64 MovableDelegate::get_unique_id() const noexcept
{
  return m_uniqueId;
}

Vector2 MovableDelegate::get_next_position(float delta) const noexcept
{
  return {m_currPosition.x + (m_velocity.x * delta),
          m_currPosition.y + (m_velocity.y * delta)};
}

}  // namespace wanderer