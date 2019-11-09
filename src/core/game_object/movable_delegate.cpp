#include "movable_delegate.h"

namespace wanderer::core {

MovableDelegate::MovableDelegate() = default;

MovableDelegate::~MovableDelegate() = default;

void MovableDelegate::Tick(float delta) {
  currPosition.Add(velocity.GetX() * delta, velocity.GetY() * delta);
}

void MovableDelegate::Move(Direction direction) noexcept {
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

void MovableDelegate::Stop(Direction direction) noexcept {
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

void MovableDelegate::Stop() noexcept {
  velocity.SetX(0);
  velocity.SetY(0);
  velocity.Norm();
  velocity.Scale(speed);
}

void MovableDelegate::SavePosition() noexcept {
  prevPosition.Set(currPosition);
}

void MovableDelegate::Interpolate(float alpha) noexcept {
  prevPosition.Interpolate(currPosition, alpha);
}

void MovableDelegate::SetSpeed(float speed) noexcept {
  this->speed = speed;
  velocity.Norm();
  velocity.Scale(speed);
}

Vector2 MovableDelegate::GetVelocity() const noexcept {
  return velocity;
}

Vector2 MovableDelegate::GetPosition() const noexcept {
  return currPosition;
}

Vector2 MovableDelegate::GetPreviousPosition() const noexcept {
  return prevPosition;
}

}