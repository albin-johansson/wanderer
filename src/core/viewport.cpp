#include "viewport.h"
#include <stdexcept>

namespace albinjohansson::wanderer {

Viewport::Viewport() : Viewport({10, 10}, {10, 10}) {}

Viewport::Viewport(Area viewport, Area level) : level(level) {
  if (viewport.width < 1 || viewport.height < 1 || level.width < 1 || level.height < 1) {
    throw std::invalid_argument("Invalid dimensions!");
  }
  bounds.SetWidth(viewport.width);
  bounds.SetHeight(viewport.height);
}

void Viewport::track(float tx, float ty, Area size, float delta) noexcept {
  const float panSpeed = 15.0f * delta;

  float targetX = (tx + (size.width / 2.0f)) - (bounds.GetWidth() / 2.0f);
  float targetY = (ty + (size.height / 2.0f)) - (bounds.GetHeight() / 2.0f);
  float x = bounds.GetX() + (targetX - bounds.GetX()) * panSpeed;
  float y = bounds.GetY() + (targetY - bounds.GetY()) * panSpeed;

  if (x < 0) {
    x = 0;
  }

  if (y < 0) {
    y = 0;
  }

  float widthDiff = level.width - bounds.GetWidth();
  x = (x > widthDiff) ? widthDiff : x;

  float heightDiff = level.height - bounds.GetHeight();
  y = (y > heightDiff) ? heightDiff : y;

  bounds.SetX(x);
  bounds.SetY(y);
}

void Viewport::center(float x, float y, Area size) noexcept {
  float x = (x + (size.width / 2.0f)) - (bounds.GetWidth() / 2.0f);
  float y = (y + (size.height / 2.0f)) - (bounds.GetHeight() / 2.0f);

  if (x < 0) {
    x = 0;
  }

  if (y < 0) {
    y = 0;
  }

  float widthDiff = level.width - bounds.GetWidth();
  x = (x > widthDiff) ? widthDiff : x;

  float heightDiff = level.height - bounds.GetHeight();
  y = (y > heightDiff) ? heightDiff : y;

  bounds.SetX(x);
  bounds.SetY(y);
}

void Viewport::set_x(float x) noexcept {
  bounds.SetX(x);
}

void Viewport::set_y(float y) noexcept {
  bounds.SetY(y);
}

void Viewport::set_width(float width) {
  bounds.SetWidth(width);
}

void Viewport::set_height(float height) {
  bounds.SetHeight(height);
}

void Viewport::set_level_width(float levelWidth) {
  if (levelWidth <= 0) {
    throw std::invalid_argument("Invalid level width!");
  } else {
    level.width = levelWidth;
  }
}

void Viewport::set_level_height(float levelHeight) {
  if (levelHeight <= 0) {
    throw std::invalid_argument("Invalid level height!");
  } else {
    level.height = levelHeight;
  }
}

const FRectangle& Viewport::get_bounds() const noexcept {
  return bounds;
}

float Viewport::get_translated_x(float x) const noexcept {
  return x - bounds.GetX();
}

float Viewport::get_translated_y(float y) const noexcept {
  return y - bounds.GetY();
}

}
