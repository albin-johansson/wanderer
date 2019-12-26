#include "rectangle.h"
#include <stdexcept>
#include <cmath>

namespace albinjohansson::wanderer {

Rectangle::Rectangle() = default;

Rectangle::Rectangle(int x, int y, int width, int height)
    : x(x), y(y), width(width), height(height) {}

Rectangle::Rectangle(const Rectangle& other) = default;

Rectangle::Rectangle(SDL_Rect rect) : x(rect.x), y(rect.y), width(rect.w), height(rect.h) {}

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

Rectangle::operator FRectangle() const noexcept {
  return {static_cast<float>(x),
          static_cast<float>(y),
          static_cast<float>(width),
          static_cast<float>(height)
  };
}

Rectangle::operator SDL_Rect() const noexcept {
  return {x, y, width, height};
}

Rectangle::operator SDL_FRect() const noexcept {
  return {static_cast<float>(x),
          static_cast<float>(y),
          static_cast<float>(width),
          static_cast<float>(height)
  };
}

FRectangle::FRectangle() noexcept : FRectangle(0, 0, 10, 10) {}

FRectangle::FRectangle(float x, float y, float width, float height) : x(x),
                                                                      y(y),
                                                                      width(width),
                                                                      height(height) {
  if (width <= 0 || height <= 0) {
    throw std::invalid_argument("Invalid dimensions!");
  }
}

FRectangle::FRectangle(SDL_FRect rect) : x(rect.x), y(rect.y), width(rect.w), height(rect.h) {}

FRectangle::FRectangle(SDL_Rect rect) : x(static_cast<float>(rect.x)),
                                        y(static_cast<float>(rect.y)),
                                        width(static_cast<float>(rect.w)),
                                        height(static_cast<float>(rect.h)) {}

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

FRectangle::operator Rectangle() const noexcept {
  return {static_cast<int>(x),
          static_cast<int>(y),
          static_cast<int>(width),
          static_cast<int>(height)
  };
}

FRectangle::operator SDL_Rect() const noexcept {
  return {static_cast<int>(std::round(x)),
          static_cast<int>(std::round(y)),
          static_cast<int>(std::round(width)),
          static_cast<int>(std::round(height))
  };
}

FRectangle::operator SDL_FRect() const noexcept {
  return {x, y, width, height};
}

}
