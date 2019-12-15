#include "rectangle.h"
#include <stdexcept>

namespace albinjohansson::wanderer {

Rectangle::Rectangle() noexcept : Rectangle(0, 0, 10, 10) {}

Rectangle::Rectangle(float x, float y, float width, float height) : x(x),
                                                                    y(y),
                                                                    width(width),
                                                                    height(height) {
  if (width <= 0 || height <= 0) {
    throw std::invalid_argument("Invalid dimensions!");
  }
}

Rectangle::Rectangle(const Rectangle& rectangle) noexcept
    : Rectangle(rectangle.x, rectangle.y, rectangle.width, rectangle.height) {}

void Rectangle::MoveX(float dx) noexcept {
  x += dx;
}

void Rectangle::MoveY(float dy) noexcept {
  y += dy;
}

void Rectangle::Set(const Rectangle& other) noexcept {
  x = other.x;
  y = other.y;
  width = other.width;
  height = other.height;
}

void Rectangle::SetX(float x) noexcept {
  this->x = x;
}

void Rectangle::SetY(float y) noexcept {
  this->y = y;
}

void Rectangle::SetWidth(float width) {
  if (width <= 0) {
    throw std::invalid_argument("Invalid width!");
  } else {
    this->width = width;
  }
}

void Rectangle::SetHeight(float height) {
  if (height <= 0) {
    throw std::invalid_argument("Invalid height!");
  } else {
    this->height = height;
  }
}

bool Rectangle::Contains(float px, float py) const noexcept {
  return !(px < x || py < y || px > GetMaxX() || py > GetMaxY());
}

bool Rectangle::Intersects(const Rectangle& r) const noexcept {
  return !(x >= r.GetMaxX() || GetMaxX() <= r.x || y >= r.GetMaxY() || GetMaxY() <= r.y);
}

float Rectangle::GetX() const noexcept { return x; }

float Rectangle::GetY() const noexcept { return y; }

float Rectangle::GetWidth() const noexcept { return width; }

float Rectangle::GetHeight() const noexcept { return height; }

float Rectangle::GetCenterX() const noexcept { return x + (width / 2.0f); }

float Rectangle::GetCenterY() const noexcept { return y + (height / 2.0f); }

float Rectangle::GetMaxX() const noexcept { return x + width; }

float Rectangle::GetMaxY() const noexcept { return y + height; }

SDL_Rect Rectangle::ToSdlRect() const noexcept {
  int ix = static_cast<int>(x);
  int iy = static_cast<int>(y);
  int iw = static_cast<int>(width);
  int ih = static_cast<int>(height);
  return {ix, iy, iw, ih};
}

}