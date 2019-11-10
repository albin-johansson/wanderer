#include "viewport.h"

namespace wanderer::core {

Viewport::Viewport(int vpWidth, int vpHeight, int levelWidth, int levelHeight) noexcept
    : levelWidth(levelWidth), levelHeight(levelHeight) {
  bounds.SetWidth(vpWidth);
  bounds.SetHeight(vpHeight);
}

void Viewport::Center(float ox, float oy, int width, int height) noexcept {
  auto x = (ox + (width / 2.0)) - (bounds.GetWidth() / 2.0);
  auto y = (oy + (height / 2.0)) - (bounds.GetHeight() / 2.0);

  if (x < 0) {
    x = 0;
  }

  if (y < 0) {
    y = 0;
  }

  if (x > (levelWidth - bounds.GetWidth())) {
    x = levelWidth - bounds.GetWidth();
  }
  if (y > (levelHeight - bounds.GetHeight())) {
    y = levelHeight - bounds.GetHeight();
  }

  bounds.SetX(x);
  bounds.SetY(y);
}

void Viewport::SetLevelWidth(int levelWidth) noexcept {
  this->levelWidth = levelWidth;
}

void Viewport::SetLevelHeight(int levelHeight) noexcept {
  this->levelHeight = levelHeight;
}

}
