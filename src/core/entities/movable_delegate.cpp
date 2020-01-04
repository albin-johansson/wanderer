#include "movable_delegate.h"
#include "game_object.h"
#include "rectangle.h"
#include "random_utils.h"
#include <stdexcept>
#include <cstdint>

using namespace centurion;

namespace albinjohansson::wanderer {

MovableDelegate::MovableDelegate(int depth, float width, float height)
    : depth(depth), width(width), height(height) {
  if (width < 1 || height < 1) {
    throw std::invalid_argument("Invalid dimensions!");
  }
  uniqueId = RandomUtils::GetRand(); // FIXME
}

MovableDelegate::~MovableDelegate() = default;

void MovableDelegate::Draw(const Renderer&, const Viewport&) const noexcept {
  /* do nothing */
}

void MovableDelegate::tick(IWandererCore&, float /*delta*/) {
  SavePosition();
  UpdatePosition();
  UpdateDirection();
}

void MovableDelegate::SavePosition() noexcept {
  prevPosition.Set(currPosition);
}

void MovableDelegate::UpdatePosition() {
  hitbox.SetX(currPosition.x);
  hitbox.SetY(currPosition.y);
}

void MovableDelegate::UpdateDirection() {
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
  velocity.Norm();
  velocity.Scale(speed);
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
  velocity.Norm();
  velocity.Scale(speed);
}

void MovableDelegate::stop() noexcept {
  velocity.Zero();
}

void MovableDelegate::interpolate(float alpha) noexcept {
  interpolatedPosition.Set(currPosition);
  interpolatedPosition.Interpolate(prevPosition, alpha);
}

void MovableDelegate::set_speed(float speed) noexcept {
  this->speed = speed;
  velocity.Norm();
  velocity.Scale(speed);
}

void MovableDelegate::add_x(float dx) noexcept {
  currPosition.Add(dx, 0);
  UpdatePosition();
}

void MovableDelegate::add_y(float dy) noexcept {
  currPosition.Add(0, dy);
  UpdatePosition();
}

void MovableDelegate::set_x(float x) noexcept {
  currPosition.x = x;
  UpdatePosition();
}

void MovableDelegate::set_y(float y) noexcept {
  currPosition.y = y;
  UpdatePosition();
}

void MovableDelegate::set_velocity(const Vector2& v) noexcept {
  velocity.Set(v);
}

void MovableDelegate::add_hitbox(const FRectangle& rectangle, const Vector2& offset) {
  hitbox.AddRectangle(rectangle, offset);
  UpdatePosition();
}

void MovableDelegate::set_blocked(bool blocked) noexcept {
  hitbox.SetEnabled(blocked);
}

int MovableDelegate::GetDepth() const noexcept {
  return depth;
}

float MovableDelegate::GetCenterY() const noexcept {
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
  return other && hitbox.WillIntersect(other->get_hitbox(), get_next_position(delta));
}

uint64_t MovableDelegate::get_unique_id() const noexcept {
  return uniqueId;
}

Vector2 MovableDelegate::get_next_position(float delta) const noexcept {
  return {currPosition.x + (velocity.x * delta), currPosition.y + (velocity.y * delta)};
}

}