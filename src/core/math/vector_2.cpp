#include "vector_2.h"
#include <cmath>

namespace wanderer::core {

Vector2::Vector2() : Vector2(0, 0) {}

Vector2::Vector2(float x, float y) {
  this->x = x;
  this->y = y;
}

Vector2::Vector2(const Vector2& vector) : Vector2(vector.x, vector.y) {}

bool Vector2::AreEqual(float a, float b, float epsilon) const noexcept {
  return fabsf(a - b) < epsilon;
}

void Vector2::Scale(float factor) {
  x *= factor;
  y *= factor;
}

void Vector2::Norm() {
  float length = GetLength();
  if (length != 0) {
    x /= length;
    y /= length;
  }
}

void Vector2::SetX(float x) noexcept {
  this->x = x;
}

void Vector2::Set(const Vector2& vector) noexcept {
  x = vector.x;
  y = vector.y;
}

void Vector2::Add(float x, float y) noexcept {
  this->x += x;
  this->y += y;
}

void Vector2::SetY(float y) noexcept {
  this->y = y;
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

float Vector2::GetLength() const noexcept {
  return sqrtf((x * x) + (y * y));
}

float Vector2::GetLength2() const noexcept {
  return (x * x) + (y * y);
}

bool Vector2::IsZero() const noexcept {
  return AreEqual(x, 0, 0.001f) && AreEqual(y, 0, 0.001f);
}

bool Vector2::IsUnit() const noexcept {
  return AreEqual(GetLength2(), 1.0f, 0.001f);
}

}