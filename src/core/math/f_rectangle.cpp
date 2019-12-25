#include "f_rectangle.h"
#include <stdexcept>

namespace albinjohansson::wanderer {

FRectangle::FRectangle() noexcept : FRectangle(0, 0, 10, 10) {}

FRectangle::FRectangle(float x, float y, float width, float height) : x(x),
                                                                      y(y),
                                                                      width(width),
                                                                      height(height) {
  if (width <= 0 || height <= 0) {
    throw std::invalid_argument("Invalid dimensions!");
  }
}

FRectangle::FRectangle(const FRectangle& rectangle) noexcept
    : FRectangle(rectangle.x, rectangle.y, rectangle.width, rectangle.height) {}

void FRectangle::MoveX(float dx) noexcept {
  x += dx;
}

void FRectangle::MoveY(float dy) noexcept {
  y += dy;
}

void FRectangle::Set(const FRectangle& other) noexcept {
  x = other.x;
  y = other.y;
  width = other.width;
  height = other.height;
}

void FRectangle::SetX(float x) noexcept {
  this->x = x;
}

void FRectangle::SetY(float y) noexcept {
  this->y = y;
}

void FRectangle::SetWidth(float width) {
  if (width <= 0) {
    throw std::invalid_argument("Invalid width!");
  } else {
    this->width = width;
  }
}

void FRectangle::SetHeight(float height) {
  if (height <= 0) {
    throw std::invalid_argument("Invalid height!");
  } else {
    this->height = height;
  }
}

bool FRectangle::Contains(float px, float py) const noexcept {
  return !(px < x || py < y || px > GetMaxX() || py > GetMaxY());
}

bool FRectangle::Intersects(const FRectangle& r) const noexcept {
  return !(x >= r.GetMaxX() || GetMaxX() <= r.x || y >= r.GetMaxY() || GetMaxY() <= r.y);
}

float FRectangle::GetX() const noexcept { return x; }

float FRectangle::GetY() const noexcept { return y; }

float FRectangle::GetWidth() const noexcept { return width; }

float FRectangle::GetHeight() const noexcept { return height; }

float FRectangle::GetCenterX() const noexcept { return x + (width / 2.0f); }

float FRectangle::GetCenterY() const noexcept { return y + (height / 2.0f); }

float FRectangle::GetMaxX() const noexcept { return x + width; }

float FRectangle::GetMaxY() const noexcept { return y + height; }

SDL_FRect FRectangle::ToSdlRect() const noexcept {
  return {x, y, width, height};
}

}