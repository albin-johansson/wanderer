#include "rectangle.h"
#include <stdexcept>

namespace wanderer::core {

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

}