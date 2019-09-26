#include "vector_2.h"
#include <cmath>
#include <stdexcept>

namespace wanderer::model {

void Vector2::Add(const Vector2& vec) noexcept {
  x += vec.x;
  y += vec.y;
}

void Vector2::Sub(const Vector2& vec) noexcept {
  x -= vec.x;
  y -= vec.y;
}

void Vector2::Mul(const Vector2& vec) noexcept {
  x *= vec.x;
  y *= vec.y;
}

void Vector2::Scale(double factor) noexcept {
  if (factor == 1) {
    return;
  } else if (factor == 0) {
    x = 0;
    y = 0;
  } else {
    x = static_cast<int>(round(x * factor));
    y = static_cast<int>(round(y * factor));
  }
}

void Vector2::SetMagnitude(double mag) {
  if (mag < 0) {
    throw std::invalid_argument("Invalid magnitude!");
  }
  int magnitude = GetMagnitude();
  x = static_cast<int>(round((x * mag) / magnitude));
  y = static_cast<int>(round((y * mag) / magnitude));
}

void Vector2::SetX(int x) noexcept {
  this->x = x;
}

void Vector2::SetY(int y) noexcept {
  this->y = y;
}

int Vector2::GetMagnitude() const noexcept {
  return static_cast<int>(round(sqrt((x * x) + (y * y))));
}

}