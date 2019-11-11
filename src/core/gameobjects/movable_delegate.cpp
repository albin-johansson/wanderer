#include "movable_delegate.h"

namespace wanderer::core {

MovableObjectDelegate::MovableObjectDelegate(int width, int height)
    : width(width), height(height) {}

MovableObjectDelegate::~MovableObjectDelegate() = default;

void MovableObjectDelegate::Tick(float delta) {
  currPosition.Add(velocity.GetX() * delta, velocity.GetY() * delta);
}

void MovableObjectDelegate::Move(Direction direction) noexcept {
  switch (direction) {
    case Direction::RIGHT: {
      velocity.SetX(speed);
      break;
    }
    case Direction::LEFT: {
      velocity.SetX(-speed);
      break;
    }
    case Direction::UP: {
      velocity.SetY(-speed);
      break;
    }
    case Direction::DOWN: {
      velocity.SetY(speed);
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
      velocity.SetX(0);
      break;
    }
    case Direction::UP:
    case Direction::DOWN: {
      velocity.SetY(0);
      break;
    }
  }
  velocity.Norm();
  velocity.Scale(speed);
}

void MovableObjectDelegate::Stop() noexcept {
  velocity.SetX(0);
  velocity.SetY(0);
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
  return currPosition.GetX();
}

float MovableObjectDelegate::GetY() const noexcept {
  return currPosition.GetY();
}

Rectangle MovableObjectDelegate::GetHitbox() const noexcept {
  return Rectangle(currPosition.GetX(), currPosition.GetY(), width, height);
}

}