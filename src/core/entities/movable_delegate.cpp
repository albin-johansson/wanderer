#include "movable_delegate.h"
#include "game_object.h"
#include "rectangle.h"
#include "random_utils.h"
#include <stdexcept>
#include <cstdint>

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

void MovableDelegate::Tick(IWandererCore&, float /*delta*/) {
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

void MovableDelegate::Move(Direction direction) noexcept {
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

void MovableDelegate::Stop(Direction direction) noexcept {
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

void MovableDelegate::Stop() noexcept {
  velocity.Zero();
}

void MovableDelegate::Interpolate(float alpha) noexcept {
  interpolatedPosition.Set(currPosition);
  interpolatedPosition.Interpolate(prevPosition, alpha);
}

void MovableDelegate::SetSpeed(float speed) noexcept {
  this->speed = speed;
  velocity.Norm();
  velocity.Scale(speed);
}

void MovableDelegate::AddX(float dx) noexcept {
  currPosition.Add(dx, 0);
  UpdatePosition();
}

void MovableDelegate::AddY(float dy) noexcept {
  currPosition.Add(0, dy);
  UpdatePosition();
}

void MovableDelegate::SetX(float x) noexcept {
  currPosition.x = x;
  UpdatePosition();
}

void MovableDelegate::SetY(float y) noexcept {
  currPosition.y = y;
  UpdatePosition();
}

void MovableDelegate::SetVelocity(const Vector2& v) noexcept {
  velocity.Set(v);
}

void MovableDelegate::AddHitbox(const FRectangle& rectangle, const Vector2& offset) {
  hitbox.AddRectangle(rectangle, offset);
  UpdatePosition();
}

void MovableDelegate::SetBlocked(bool blocked) noexcept {
  hitbox.SetEnabled(blocked);
}

int MovableDelegate::GetDepth() const noexcept {
  return depth;
}

float MovableDelegate::GetCenterY() const noexcept {
  return currPosition.y + (height / 2.0f);
}

float MovableDelegate::GetSpeed() const noexcept {
  return speed;
}

float MovableDelegate::GetWidth() const noexcept {
  return width;
}

float MovableDelegate::GetHeight() const noexcept {
  return height;
}

float MovableDelegate::GetX() const noexcept {
  return currPosition.x;
}

float MovableDelegate::GetY() const noexcept {
  return currPosition.y;
}

const Hitbox& MovableDelegate::GetHitbox() const noexcept {
  return hitbox;
}

Direction MovableDelegate::GetDominantDirection() const noexcept {
  return dominantDirection;
}

const Vector2& MovableDelegate::GetVelocity() const noexcept {
  return velocity;
}

const Vector2& MovableDelegate::GetPosition() const noexcept {
  return currPosition;
}

const Vector2& MovableDelegate::GetInterpolatedPosition() const noexcept {
  return interpolatedPosition;
}

const Vector2& MovableDelegate::GetPreviousPosition() const noexcept {
  return prevPosition;
}

bool MovableDelegate::WillIntersect(const IGameObject* other, float delta) const {
  return other && hitbox.WillIntersect(other->GetHitbox(), GetNextPosition(delta));
}

uint64_t MovableDelegate::GetUniqueID() const noexcept {
  return uniqueId;
}

Vector2 MovableDelegate::GetNextPosition(float delta) const noexcept {
  return {currPosition.x + (velocity.x * delta), currPosition.y + (velocity.y * delta)};
}

}