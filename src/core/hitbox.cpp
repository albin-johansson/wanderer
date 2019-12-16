#include "hitbox.h"

namespace albinjohansson::wanderer {

Hitbox::Hitbox() = default;

Hitbox::~Hitbox() = default;

void Hitbox::CalcBounds() {
  bool first = true;

  for (auto& pair : rectangles) {
    const auto& rect = pair.first;

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
      bounds.SetWidth(rectMaxX - bounds.GetX());
    }

    if (rectMaxY > bounds.GetMaxY()) {
      bounds.SetHeight(rectMaxY - bounds.GetY());
    }

    pair.second.x = rectX - bounds.GetX();
    pair.second.y = rectY - bounds.GetY();
  }
}

void Hitbox::AddRectangle(const Rectangle& rect) {
  rectangles.emplace_back(rect, Vector2(0, 0));
  CalcBounds();
}

void Hitbox::SetX(float x) noexcept {
  // TODO...
  bounds.SetX(x);
  for (auto& pair : rectangles) {
    pair.first.SetX(x + pair.second.x);
  }
}

void Hitbox::SetY(float y) noexcept {
  bounds.SetY(y);
  for (auto& pair : rectangles) {
    pair.first.SetY(y + pair.second.y);
  }
}

bool Hitbox::Intersects(const Hitbox& other) const noexcept {
  if (other.IsUnit()) {
    return Intersects(other.rectangles.front().first);
  }

  // FIXME quadratic complexity
  for (const auto& pair : rectangles) {
    for (const auto& otherPair : other.rectangles) {
      if (otherPair.first.Intersects(pair.first)) {
        return true;
      }
    }
  }
  return false;
}

bool Hitbox::Intersects(const Rectangle& other) const noexcept {
  for (const auto& pair : rectangles) {
    if (pair.first.Intersects(other)) {
      return true;
    }
  }
  return false;
}

const Rectangle& Hitbox::GetBounds() const noexcept {
  return bounds;
}

int Hitbox::GetSubhitboxAmount() const noexcept {
  return rectangles.size();
}

bool Hitbox::IsUnit() const noexcept {
  return rectangles.size() == 1;
}

}
