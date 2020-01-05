#include "movable_delegate.h"
#include "game_object.h"
#include "rectangle.h"
#include "game_object_id.h"
#include <stdexcept>
#include <cstdint>

using namespace centurion;

namespace albinjohansson::wanderer {

MovableDelegate::MovableDelegate(int depth, float width, float height)
    : depth(depth), width(width), height(height) {
  if (width < 1 || height < 1) {
    throw std::invalid_argument("Invalid dimensions!");
  }
  uniqueId = GameObjectID::next();
}

MovableDelegate::~MovableDelegate() = default;

void MovableDelegate::draw(const Renderer&, const Viewport&) const noexcept {
  /* do nothing */
}

void MovableDelegate::tick(IWandererCore&, float /*delta*/) {
  save_position();
  update_position();
  update_direction();
}

void MovableDelegate::save_position() noexcept {
  prevPosition.set(currPosition);
}

void MovableDelegate::update_position() {
  hitbox.set_x(currPosition.x);
  hitbox.set_y(currPosition.y);
}

void MovableDelegate::update_direction() {
  if (velocity.x > 0) {
    dominantDirection = Direction::Right;
  } else if (velocity.x < 0) {
    dominantDirection = Direction::Left;
  } else {
    if (velocity.y < 0) {
      dominantDirection = Direction::Up;
    } else if (velocity.y > 0) {
      dominantDirection = Direction::Down;
    }
  }
}

void MovableDelegate::move(Direction direction) noexcept {
  switch (direction) {
    case Direction::Right: {
      velocity.x = speed;
      break;
    }
    case Direction::Left: {
      velocity.x = -speed;
      break;
    }
    case Direction::Up: {
      velocity.y = -speed;
      break;
    }
    case Direction::Down: {
      velocity.y = speed;
      break;
    }
  }
  velocity.norm();
  velocity.scale(speed);
}

void MovableDelegate::stop(Direction direction) noexcept {
  switch (direction) {
    case Direction::Right:
    case Direction::Left: {
      velocity.x = 0;
      break;
    }
    case Direction::Up:
    case Direction::Down: {
      velocity.y = 0;
      break;
    }
  }
  velocity.norm();
  velocity.scale(speed);
}

void MovableDelegate::stop() noexcept {
  velocity.zero();
}

void MovableDelegate::interpolate(float alpha) noexcept {
  interpolatedPosition.set(currPosition);
  interpolatedPosition.interpolate(prevPosition, alpha);
}

void MovableDelegate::set_speed(float speed) noexcept {
  this->speed = speed;
  velocity.norm();
  velocity.scale(speed);
}

void MovableDelegate::add_x(float dx) noexcept {
  currPosition.add(dx, 0);
  update_position();
}

void MovableDelegate::add_y(float dy) noexcept {
  currPosition.add(0, dy);
  update_position();
}

void MovableDelegate::set_x(float x) noexcept {
  currPosition.x = x;
  update_position();
}

void MovableDelegate::set_y(float y) noexcept {
  currPosition.y = y;
  update_position();
}

void MovableDelegate::set_velocity(const Vector2& v) noexcept {
  velocity.set(v);
}

void MovableDelegate::add_hitbox(const FRectangle& rectangle, const Vector2& offset) {
  hitbox.add_rectangle(rectangle, offset);
  update_position();
}

void MovableDelegate::set_blocked(bool blocked) noexcept {
  hitbox.set_enabled(blocked);
}

int MovableDelegate::get_depth() const noexcept {
  return depth;
}

float MovableDelegate::get_center_y() const noexcept {
  return currPosition.y + (height / 2.0f);
}

float MovableDelegate::get_speed() const noexcept {
  return speed;
}

float MovableDelegate::get_width() const noexcept {
  return width;
}

float MovableDelegate::get_height() const noexcept {
  return height;
}

float MovableDelegate::get_x() const noexcept {
  return currPosition.x;
}

float MovableDelegate::get_y() const noexcept {
  return currPosition.y;
}

const Hitbox& MovableDelegate::get_hitbox() const noexcept {
  return hitbox;
}

Direction MovableDelegate::get_dominant_direction() const noexcept {
  return dominantDirection;
}

const Vector2& MovableDelegate::get_velocity() const noexcept {
  return velocity;
}

const Vector2& MovableDelegate::get_position() const noexcept {
  return currPosition;
}

const Vector2& MovableDelegate::get_interpolated_position() const noexcept {
  return interpolatedPosition;
}

const Vector2& MovableDelegate::get_previous_position() const noexcept {
  return prevPosition;
}

bool MovableDelegate::will_intersect(const IGameObject* other, float delta) const {
  return other && hitbox.will_intersect(other->get_hitbox(), get_next_position(delta));
}

uint64_t MovableDelegate::get_unique_id() const noexcept {
  return uniqueId;
}

Vector2 MovableDelegate::get_next_position(float delta) const noexcept {
  return {currPosition.x + (velocity.x * delta), currPosition.y + (velocity.y * delta)};
}

}