#include "hitbox.h"

namespace albinjohansson::wanderer {

Hitbox::Hitbox() = default;

Hitbox::~Hitbox() = default;

void Hitbox::calc_bounds() {
  bool first = true;

  for (auto&[rect, offset] : rectangles) {

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

    offset.x = rectX - bounds.GetX();
    offset.y = rectY - bounds.GetY();
  }
}

void Hitbox::add_rectangle(const FRectangle& rect, const Vector2& offset) {
  rectangles.emplace_back(rect, offset);
  calc_bounds();
}

void Hitbox::set_x(float x) noexcept {
  bounds.SetX(x);
  for (auto&[rect, offset] : rectangles) {
    rect.SetX(x + offset.x);
  }
}

void Hitbox::set_y(float y) noexcept {
  bounds.SetY(y);
  for (auto&[rect, offset] : rectangles) {
    rect.SetY(y + offset.y);
  }
}

void Hitbox::set_enabled(bool enabled) noexcept {
  this->enabled = enabled;
}

bool Hitbox::intersects(const Hitbox& other) const noexcept {
  if (!enabled || &other == this) {
    return false;
  }

  if (other.is_unit()) {
    return intersects(other.rectangles.front().first);
  }

  for (const auto&[rect, offset] : rectangles) {
    for (const auto&[otherRect, otherOffset] : other.rectangles) {
      if (rect.Intersects(otherRect)) {
        return true;
      }
    }
  }
  return false;
}

bool Hitbox::intersects(const FRectangle& other) const noexcept {
  if (!enabled) {
    return false;
  }

  for (const auto&[rect, offset] : rectangles) {
    if (rect.Intersects(other)) {
      return true;
    }
  }
  return false;
}

bool Hitbox::will_intersect(const Hitbox& other, const Vector2& nextPos) const noexcept {
  if (!enabled) {
    return false;
  }

  const auto oldX = bounds.GetX();
  const auto oldY = bounds.GetY();

  auto tmp = const_cast<Hitbox*>(this); // Not great, but will remain unaffected

  tmp->set_x(nextPos.x);
  tmp->set_y(nextPos.y);

  bool intersection = intersects(other);

  tmp->set_x(oldX);
  tmp->set_y(oldY);

  return intersection;
}

const FRectangle& Hitbox::get_bounds() const noexcept {
  return bounds;
}

bool Hitbox::is_unit() const noexcept {
  return rectangles.size() == 1;
}

bool Hitbox::is_enabled() const noexcept {
  return enabled;
}

}
