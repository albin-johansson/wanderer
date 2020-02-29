#include "vector_2.h"

#include <cmath>

namespace albinjohansson::wanderer {

Vector2::Vector2() : Vector2(0, 0)
{}

Vector2::Vector2(const Vector2& other) : Vector2(other.x, other.y)
{}

void Vector2::scale(float factor) noexcept
{
  x *= factor;
  y *= factor;
}

void Vector2::norm() noexcept
{
  const auto length = get_length();
  if (length != 0) {
    x /= length;
    y /= length;
  }
}

void Vector2::zero() noexcept
{
  x = y = 0;
}

void Vector2::set(const Vector2& other) noexcept
{
  x = other.x;
  y = other.y;
}

void Vector2::set(float x, float y) noexcept
{
  this->x = x;
  this->y = y;
}

void Vector2::set_length(float length) noexcept
{
  if (length == 0) {
    x = 0;
    y = 0;
    return;
  }

  const auto prevLength = get_length();
  if ((prevLength == 0) || (prevLength == length)) {
    return;
  }
  scale(length / prevLength);
}

void Vector2::lerp(const Vector2& target, float alpha) noexcept
{
  const float invAlpha = 1.0f - alpha;
  this->x = (x * invAlpha) + (target.x * alpha);
  this->y = (y * invAlpha) + (target.y * alpha);
}

void Vector2::interpolate(const Vector2& target, float alpha) noexcept
{
  lerp(target, alpha * alpha * alpha * (alpha * (alpha * 6 - 15) + 10));
}

void Vector2::add(const Vector2& other) noexcept
{
  x += other.x;
  y += other.y;
}

void Vector2::add(float x, float y) noexcept
{
  this->x += x;
  this->y += y;
}

void Vector2::sub(const Vector2& other) noexcept
{
  x -= other.x;
  y -= other.y;
}

void Vector2::sub(float x, float y) noexcept
{
  this->x -= x;
  this->y -= y;
}

void Vector2::look_at(const Vector2& target) noexcept
{
  look_at(target, get_length());
}

void Vector2::look_at(const Vector2& target, float length) noexcept
{
  if (length <= 0) {
    x = 0;
    y = 0;
  } else {
    x = (target.x - x);
    y = (target.y - y);
    norm();
    scale(length);
  }
}

void Vector2::invert() noexcept
{
  x *= -1;
  y *= -1;
}

Vector2 Vector2::operator+(const Vector2& other) const noexcept
{
  return Vector2(x + other.x, y + other.y);
}

Vector2 Vector2::operator-(const Vector2& other) const noexcept
{
  return Vector2(x - other.x, y - other.y);
}

float Vector2::operator*(const Vector2& other) const noexcept
{
  return dot(other);
}

bool Vector2::operator==(const Vector2& other) const noexcept
{
  return Math::almost_equal(x, other.x) && Math::almost_equal(y, other.y);
}

bool Vector2::operator!=(const Vector2& other) const noexcept
{
  return !(*this == other);
}

float Vector2::dot(const Vector2& other) const noexcept
{
  return (x * other.x) + (y * other.y);
}

float Vector2::distance_to(const Vector2& other) const noexcept
{
  const auto xDiff = other.x - x;
  const auto yDiff = other.y - y;
  return std::sqrt((xDiff * xDiff) + (yDiff * yDiff));
}

float Vector2::distance_to_2(const Vector2& other) const noexcept
{
  const auto xDiff = other.x - x;
  const auto yDiff = other.y - y;
  return (xDiff * xDiff) + (yDiff * yDiff);
}

int Vector2::angle(const Vector2& other) const noexcept
{
  return Math::round(Math::to_degrees(std::acos(dot(other))));
}

float Vector2::get_length() const noexcept
{
  return std::sqrt((x * x) + (y * y));
}

float Vector2::get_length_2() const noexcept
{
  return (x * x) + (y * y);
}

bool Vector2::is_zero() const noexcept
{
  return Math::almost_equal(x, 0) && Math::almost_equal(y, 0);
}

bool Vector2::is_unit() const noexcept
{
  return Math::almost_equal(get_length_2(), 1.0f);
}

}  // namespace albinjohansson::wanderer
