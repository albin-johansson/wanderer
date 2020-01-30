#include "viewport.h"
#include <stdexcept>

using namespace centurion;

namespace albinjohansson::wanderer {

Viewport::Viewport() : Viewport({10, 10}, {10, 10}) {}

Viewport::Viewport(Area viewport, Area level) : level(level) {
  if (viewport.width < 1 || viewport.height < 1 || level.width < 1 || level.height < 1) {
    throw std::invalid_argument("Invalid dimensions!");
  }
  bounds.set_width(viewport.width);
  bounds.set_height(viewport.height);
}

void Viewport::track(float tx, float ty, Area size, float delta) noexcept {
  const float panSpeed = 15.0f * delta;

  const float targetX = (tx + (size.width / 2.0f)) - (bounds.get_width() / 2.0f);
  const float targetY = (ty + (size.height / 2.0f)) - (bounds.get_height() / 2.0f);
  float x = bounds.get_x() + (targetX - bounds.get_x()) * panSpeed;
  float y = bounds.get_y() + (targetY - bounds.get_y()) * panSpeed;

  if (x < 0) {
    x = 0;
  }

  if (y < 0) {
    y = 0;
  }

  const float widthDiff = level.width - bounds.get_width();
  x = (x > widthDiff) ? widthDiff : x;

  const float heightDiff = level.height - bounds.get_height();
  y = (y > heightDiff) ? heightDiff : y;

  bounds.set_x(x);
  bounds.set_y(y);
}

void Viewport::center(float tx, float ty, Area size) noexcept {
  float x = (tx + (size.width / 2.0f)) - (bounds.get_width() / 2.0f);
  float y = (ty + (size.height / 2.0f)) - (bounds.get_height() / 2.0f);

  if (x < 0) {
    x = 0;
  }

  if (y < 0) {
    y = 0;
  }

  const float widthDiff = level.width - bounds.get_width();
  x = (x > widthDiff) ? widthDiff : x;

  const float heightDiff = level.height - bounds.get_height();
  y = (y > heightDiff) ? heightDiff : y;

  bounds.set_x(x);
  bounds.set_y(y);
}

void Viewport::set_x(float x) noexcept {
  bounds.set_x(x);
}

void Viewport::set_y(float y) noexcept {
  bounds.set_y(y);
}

void Viewport::set_width(float width) {
  bounds.set_width(width);
}

void Viewport::set_height(float height) {
  bounds.set_height(height);
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

const FRect& Viewport::get_bounds() const noexcept {
  return bounds;
}

float Viewport::get_translated_x(float x) const noexcept {
  return x - bounds.get_x();
}

float Viewport::get_translated_y(float y) const noexcept {
  return y - bounds.get_y();
}

}
