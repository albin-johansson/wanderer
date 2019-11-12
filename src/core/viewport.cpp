#include "viewport.h"

namespace wanderer::core {

Viewport::Viewport(float vpWidth, float vpHeight, float levelWidth, float levelHeight) noexcept
    : levelWidth(levelWidth), levelHeight(levelHeight) {
  bounds.SetWidth(vpWidth);
  bounds.SetHeight(vpHeight);
}

void Viewport::Center(float ox, float oy, float width, float height) noexcept {
  const static float moveSpeed = 0.1f;
  const auto boundsWidth = bounds.GetWidth();
  const auto boundsHeight = bounds.GetHeight();

  float targetX = (ox + (width / 2.0f)) - (boundsWidth / 2.0f);
  float targetY = (oy + (height / 2.0f)) - (boundsHeight / 2.0f);
  float x = bounds.GetX() + (targetX - bounds.GetX()) * moveSpeed;
  float y = bounds.GetY() + (targetY - bounds.GetY()) * moveSpeed;

  if (x < 0) {
    x = 0;
  }

  if (y < 0) {
    y = 0;
  }

  float widthDiff = levelWidth - boundsWidth;
  x = (x > widthDiff) ? widthDiff : x;

  float heightDiff = levelHeight - boundsHeight;
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
