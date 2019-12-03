#include "movable_delegate.h"
#include <stdexcept>

namespace albinjohansson::wanderer {

MovableObjectDelegate::MovableObjectDelegate(float width, float height)
    : width(width), height(height) {
  if (width < 1 || height < 1) {
    throw std::invalid_argument("Invalid dimensions!");
  }
  dominantDirection = Direction::DOWN;
}

MovableObjectDelegate::~MovableObjectDelegate() = default;

IMovableObject_uptr MovableObjectDelegate::Create(float width, float height) {
  return std::make_unique<MovableObjectDelegate>(width, height);
}

void MovableObjectDelegate::Draw(Renderer& renderer,
                                 const Viewport& viewport) const noexcept {
  /* do nothing */
}

void MovableObjectDelegate::Tick(IWandererCore& core, float delta) {
  UpdateDirection();
}

void MovableObjectDelegate::UpdateDirection() {
  if (velocity.x > 0) {
    dominantDirection = Direction::RIGHT;
  } else if (velocity.x < 0) {
    dominantDirection = Direction::LEFT;
  } else {
    if (velocity.y < 0) {
      dominantDirection = Direction::UP;
    } else if (velocity.y > 0) {
      dominantDirection = Direction::DOWN;
    }
  }
}

void MovableObjectDelegate::Move(Direction direction) noexcept {
  switch (direction) {
    case Direction::RIGHT: {
      velocity.x = speed;
      break;
    }
    case Direction::LEFT: {
      velocity.x = -speed;
      break;
    }
    case Direction::UP: {
      velocity.y = -speed;
      break;
    }
    case Direction::DOWN: {
      velocity.y = speed;
      break;
    }
  }
  velocity.Norm();
  velocity.Scale(speed);
}

void MovableObjectDelegate::Stop(Direction direction) noexcept {
  switch (direction) {
    case Direction::RIGHT:
    case Direction::LEFT: {
      velocity.x = 0;
      break;
    }
    case Direction::UP:
    case Direction::DOWN: {
      velocity.y = 0;
      break;
    }
  }
  velocity.Norm();
  velocity.Scale(speed);
}

void MovableObjectDelegate::Stop() noexcept {
  velocity.x = 0;
  velocity.y = 0;
  velocity.Norm();
  velocity.Scale(speed);
}

void MovableObjectDelegate::SavePosition() noexcept {
  prevPosition.Set(currPosition);
}

void MovableObjectDelegate::Interpolate(float alpha) noexcept {
  interpolatedPosition.Set(currPosition);
  interpolatedPosition.Interpolate(prevPosition, alpha);
}

void MovableObjectDelegate::SetSpeed(float speed) noexcept {
  this->speed = speed;
  velocity.Norm();
  velocity.Scale(speed);
}

float MovableObjectDelegate::GetX() const noexcept {
  return currPosition.x;
}

float MovableObjectDelegate::GetY() const noexcept {
  return currPosition.y;
}

Rectangle MovableObjectDelegate::GetHitbox() const noexcept {
  return Rectangle(currPosition.x, currPosition.y, width, height);
}

void MovableObjectDelegate::AddX(float dx) noexcept {
  currPosition.Add(dx, 0);
}

void MovableObjectDelegate::AddY(float dy) noexcept {
  currPosition.Add(0, dy);
}

void MovableObjectDelegate::SetX(float x) noexcept {
  currPosition.x = x;
}

void MovableObjectDelegate::SetY(float y) noexcept {
  currPosition.y = y;
}

void MovableObjectDelegate::SetVelocity(const Vector2& v) noexcept {
  velocity.Set(v);
}

}