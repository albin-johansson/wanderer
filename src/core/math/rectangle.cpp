#include "rectangle.h"

namespace albinjohansson::wanderer {

Rectangle::Rectangle() = default;

Rectangle::Rectangle(int x, int y, int width, int height)
    : x(x), y(y), width(width), height(height) {}

Rectangle::Rectangle(const Rectangle& other) = default;

Rectangle::~Rectangle() noexcept = default;

void Rectangle::MoveX(int dx) noexcept {
  x += dx;
}

void Rectangle::MoveY(int dy) noexcept {
  y += dy;
}

void Rectangle::Set(const Rectangle& other) noexcept {
  x = other.x;
  y = other.y;
  width = other.width;
  height = other.height;
}

void Rectangle::SetX(int x) noexcept {
  this->x = x;
}

void Rectangle::SetY(int y) noexcept {
  this->y = y;
}

void Rectangle::SetWidth(int width) {
  this->width = width;
}

void Rectangle::SetHeight(int height) {
  this->height = height;
}

bool Rectangle::Contains(int px, int py) const noexcept {
  return !(px < x || py < y || px > GetMaxX() || py > GetMaxY());
}

bool Rectangle::Intersects(const Rectangle& r) const noexcept {
  return !(x >= r.GetMaxX() || GetMaxX() <= r.x || y >= r.GetMaxY() || GetMaxY() <= r.y);
}

int Rectangle::GetX() const noexcept {
  return x;
}

int Rectangle::GetY() const noexcept {
  return y;
}

int Rectangle::GetWidth() const noexcept {
  return width;
}

int Rectangle::GetHeight() const noexcept {
  return height;
}

int Rectangle::GetCenterX() const noexcept {
  return x + (width / 2);
}

int Rectangle::GetCenterY() const noexcept {
  return y + (height / 2);
}

int Rectangle::GetMaxX() const noexcept {
  return x + width;
}

int Rectangle::GetMaxY() const noexcept {
  return y + height;
}

SDL_Rect Rectangle::ToSdlRect() const noexcept {
  return {x, y, width, height};
}

}
