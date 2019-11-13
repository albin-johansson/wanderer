#include "viewport.h"

namespace wanderer::core {

Viewport::Viewport(float vpWidth, float vpHeight, float levelWidth, float levelHeight) noexcept
    : levelWidth(levelWidth), levelHeight(levelHeight) {
  bounds.SetWidth(vpWidth);
  bounds.SetHeight(vpHeight);
}

void Viewport::Center(float ox, float oy, float width, float height) noexcept {
  const static float panSpeed = 0.08f;

  float targetX = (ox + (width / 2.0f)) - (bounds.GetWidth() / 2.0f);
  float targetY = (oy + (height / 2.0f)) - (bounds.GetHeight() / 2.0f);
  float x = bounds.GetX() + (targetX - bounds.GetX()) * panSpeed;
  float y = bounds.GetY() + (targetY - bounds.GetY()) * panSpeed;

  if (x < 0) {
    x = 0;
  }

  if (y < 0) {
    y = 0;
  }

  float widthDiff = levelWidth - bounds.GetWidth();
  x = (x > widthDiff) ? widthDiff : x;

  float heightDiff = levelHeight - bounds.GetHeight();
  y = (y > heightDiff) ? heightDiff : y;

  bounds.SetX(x);
  bounds.SetY(y);
}

void Viewport::SetLevelWidth(float levelWidth) noexcept {
  this->levelWidth = levelWidth;
}

void Viewport::SetWidth(float width) noexcept {
  bounds.SetWidth(width);
}

void Viewport::SetHeight(float height) noexcept {
  bounds.SetHeight(height);
}

void Viewport::SetLevelHeight(float levelHeight) noexcept {
  this->levelHeight = levelHeight;
}

}
