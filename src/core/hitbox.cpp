#include "hitbox.h"

namespace albinjohansson::wanderer {

Hitbox::Hitbox() = default;

Hitbox::~Hitbox() = default;

void Hitbox::CalcBounds() {
  bool first = true;

  for (const auto& rect : rectangles) {
    if (first) {
      bounds.Set(rect);
      first = false;
    }

    const auto rectX = rect.GetX();
    const auto rectY = rect.GetY();
    const auto rectMaxX = rect.GetMaxX();
    const auto rectMaxY = rect.GetMaxY();

    if (rectX < bounds.GetX()) {
      bounds.SetX(rectX);
    }

    if (rectY < bounds.GetY()) {
      bounds.SetY(rectY);
    }

    if (rectMaxX > bounds.GetMaxX()) {
      const auto xDiff = rectX - bounds.GetMaxX();
      bounds.SetWidth(bounds.GetWidth() + rect.GetWidth() + xDiff);
    }

    if (rectMaxY > bounds.GetMaxY()) {
      const auto yDiff = rectY - bounds.GetMaxY();
      bounds.SetHeight(bounds.GetHeight() + rect.GetHeight() + yDiff);
    }
  }
}

void Hitbox::AddRectangle(const Rectangle& rect) {
  rectangles.push_back(rect);
  CalcBounds();
}

bool Hitbox::Intersects(const Hitbox& other) const noexcept {
  // FIXME quadratic complexity
  for (const auto& rect : rectangles) {
    for (const auto& otherRect : other.rectangles) {
      if (otherRect.Intersects(rect)) {
        return true;
      }
    }
  }
  return false;
}

}
