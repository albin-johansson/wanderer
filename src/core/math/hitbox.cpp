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

    auto& offset = pair.second;
    offset.x = rectX - bounds.GetX();
    offset.y = rectY - bounds.GetY();
  }
}

void Hitbox::AddRectangle(const FRectangle& rect, const Vector2& offset) {
  rectangles.emplace_back(rect, offset);
  CalcBounds();
}

void Hitbox::SetX(float x) noexcept {
  bounds.SetX(x);
  for (auto& pair : rectangles) {
    auto& rect = pair.first;
    const auto& offset = pair.second;

    rect.SetX(x + offset.x);
  }
}

void Hitbox::SetY(float y) noexcept {
  bounds.SetY(y);
  for (auto& pair : rectangles) {
    auto& rect = pair.first;
    const auto& offset = pair.second;

    rect.SetY(y + offset.y);
  }
}

void Hitbox::SetEnabled(bool enabled) noexcept {
  this->enabled = enabled;
}

bool Hitbox::Intersects(const Hitbox& other) const noexcept {
  if (!enabled) {
    return false;
  }

  if (other.IsUnit()) {
    return Intersects(other.rectangles.front().first);
  }

  for (const auto& pair : rectangles) {
    const auto& rect = pair.first;

    for (const auto& otherPair : other.rectangles) {
      const auto& otherRect = otherPair.first;
      if (rect.Intersects(otherRect)) {
        return true;
      }
    }

  }
  return false;
}

bool Hitbox::Intersects(const FRectangle& other) const noexcept {
  if (!enabled) {
    return false;
  }

  for (const auto& pair : rectangles) {
    const auto& rect = pair.first;
    if (rect.Intersects(other)) {
      return true;
    }
  }
  return false;
}

bool Hitbox::WillIntersect(const Hitbox& other, const Vector2& nextPos) const noexcept {
  if (!enabled) {
    return false;
  }

  const auto oldX = bounds.GetX();
  const auto oldY = bounds.GetY();

  auto tmp = const_cast<Hitbox*>(this); // Not great, but will remain unaffected

  tmp->SetX(nextPos.x);
  tmp->SetY(nextPos.y);

  bool intersects = Intersects(other);

  tmp->SetX(oldX);
  tmp->SetY(oldY);

  return intersects;
}

const FRectangle& Hitbox::GetBounds() const noexcept {
  return bounds;
}

bool Hitbox::IsUnit() const noexcept {
  return rectangles.size() == 1;
}

bool Hitbox::IsEnabled() const noexcept {
  return enabled;
}

}
