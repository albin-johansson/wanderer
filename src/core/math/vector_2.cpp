#include "vector_2.h"
#include "math_utils.h"
#include <cmath>

namespace albinjohansson::wanderer {

Vector2::Vector2() : Vector2(0, 0) {}

Vector2::Vector2(float x, float y) {
  this->x = x;
  this->y = y;
}

Vector2::Vector2(const Vector2& vector) : Vector2(vector.x, vector.y) {}

void Vector2::Scale(float factor) noexcept {
  x *= factor;
  y *= factor;
}

void Vector2::Norm() noexcept {
  float length = GetLength();
  if (length != 0) {
    x /= length;
    y /= length;
  }
}

void Vector2::Zero() noexcept {
  x = y = 0;
}

void Vector2::Set(const Vector2& vector) noexcept {
  x = vector.x;
  y = vector.y;
}

Vector2 Vector2::operator+(const Vector2& v) const noexcept {
  return Vector2(x + v.x, y + v.y);
}

Vector2 Vector2::operator-(const Vector2& v) const noexcept {
  return Vector2(x - v.x, y - v.y);
}

bool Vector2::operator==(const Vector2& v) const noexcept {
  return MathUtils::AlmostEqual(x, v.x)
      && MathUtils::AlmostEqual(y, v.y);
}

bool Vector2::operator!=(const Vector2& v) const noexcept {
  return !(*this == v);
}

void Vector2::Add(float x, float y) noexcept {
  this->x += x;
  this->y += y;
}

void Vector2::SetLength(float length) noexcept {
  if (length == 0) {
    x = 0;
    y = 0;
    return;
  }

  float prevLength = GetLength();
  if ((prevLength == 0) || (prevLength == length)) {
    return;
  }
  Scale(length / prevLength);
}

void Vector2::Lerp(const Vector2& target, float alpha) noexcept {
  float invAlpha = 1.0f - alpha;
  this->x = (x * invAlpha) + (target.x * alpha);
  this->y = (y * invAlpha) + (target.y * alpha);
}

void Vector2::Interpolate(const Vector2& target, float alpha) noexcept {
  Lerp(target, alpha * alpha * alpha * (alpha * (alpha * 6 - 15) + 10));
}

void Vector2::Add(const Vector2& vector) noexcept {
  x += vector.x;
  y += vector.y;
}

void Vector2::Sub(const Vector2& vector) noexcept {
  x -= vector.x;
  y -= vector.y;
}

void Vector2::LookAt(const Vector2& target) noexcept {
  auto magnitude = GetLength();
  x = (target.x - x);
  y = (target.y - y);
  Norm();
  Scale(magnitude);
}

void Vector2::LookAt(const Vector2& target, float length) noexcept {
  if (length <= 0) {
    x = 0;
    y = 0;
  } else {
    x = (target.x - x);
    y = (target.y - y);
    Norm();
    Scale(length);
  }
}

//void Vector2::SetAngle(float angle) noexcept {
//  static constexpr float TO_RADIANS = 3.14f / 180.0f;
//
//  x = GetLength();
//  y = 0;
//
//  float radians = angle * TO_RADIANS;
//
//  float cos = std::cos(radians);
//  float sin = std::sin(radians);
//
//  x = (x * cos) - (y * sin);
//  y = (x * sin) + (y * cos);
//}

float Vector2::DistanceTo(const Vector2& vector) const noexcept {
  auto xDiff = vector.x - x;
  auto yDiff = vector.y - y;
  return std::sqrt((xDiff * xDiff) + (yDiff * yDiff));
}

float Vector2::DistanceTo2(const Vector2& vector) const noexcept {
  auto xDiff = vector.x - x;
  auto yDiff = vector.y - y;
  return (xDiff * xDiff) + (yDiff * yDiff);
}

//float Vector2::GetAngle() const noexcept {
//  return (std::atan2(y, x) / 3.14f) * 180.0f;
//}

float Vector2::GetLength() const noexcept {
  return std::sqrt((x * x) + (y * y));
}

float Vector2::GetLength2() const noexcept {
  return (x * x) + (y * y);
}

bool Vector2::IsZero() const noexcept {
  return MathUtils::AlmostEqual(x, 0)
      && MathUtils::AlmostEqual(y, 0);
}

bool Vector2::IsUnit() const noexcept {
  return MathUtils::AlmostEqual(GetLength2(), 1.0f);
}

}