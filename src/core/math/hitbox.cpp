#include "hitbox.h"

using namespace centurion;

namespace albinjohansson::wanderer {

Hitbox::Hitbox() = default;

Hitbox::~Hitbox() = default;

void Hitbox::calc_bounds() {
  bool first = true;

  for (auto&[rect, offset] : rectangles) {

    if (first) {
      bounds.set_x(rect.get_x());
      bounds.set_y(rect.get_y());
      bounds.set_width(rect.get_width());
      bounds.set_height(rect.get_height());
//      bounds.Set(rect); // TODO add to CTN 3.1.0
      first = false;
    }

    const auto rectX = rect.get_x();
    const auto rectY = rect.get_y();
    const auto rectMaxX = rect.get_max_x();
    const auto rectMaxY = rect.get_max_y();

    if (rectX < bounds.get_x()) {
      bounds.set_x(rectX);
    }

    if (rectY < bounds.get_y()) {
      bounds.set_y(rectY);
    }

    if (rectMaxX > bounds.get_max_x()) {
      bounds.set_width(rectMaxX - bounds.get_x());
    }

    if (rectMaxY > bounds.get_max_y()) {
      bounds.set_height(rectMaxY - bounds.get_y());
    }

    offset.x = rectX - bounds.get_x();
    offset.y = rectY - bounds.get_y();
  }
}

void Hitbox::add_rectangle(const FRect& rect, const Vector2& offset) {
  rectangles.emplace_back(rect, offset);
  calc_bounds();
}

void Hitbox::set_x(float x) noexcept {
  bounds.set_x(x);
  for (auto&[rect, offset] : rectangles) {
    rect.set_x(x + offset.x);
  }
}

void Hitbox::set_y(float y) noexcept {
  bounds.set_y(y);
  for (auto&[rect, offset] : rectangles) {
    rect.set_y(y + offset.y);
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
      if (rect.intersects(otherRect)) {
        return true;
      }
    }
  }
  return false;
}

bool Hitbox::intersects(const FRect& other) const noexcept {
  if (!enabled) {
    return false;
  }

  for (const auto&[rect, offset] : rectangles) {
    if (rect.intersects(other)) {
      return true;
    }
  }
  return false;
}

bool Hitbox::will_intersect(const Hitbox& other, const Vector2& nextPos) const noexcept {
  if (!enabled) {
    return false;
  }

  const auto oldX = bounds.get_x();
  const auto oldY = bounds.get_y();

  auto tmp = const_cast<Hitbox*>(this); // Not great, but will remain unaffected

  tmp->set_x(nextPos.x);
  tmp->set_y(nextPos.y);

  bool intersection = intersects(other);

  tmp->set_x(oldX);
  tmp->set_y(oldY);

  return intersection;
}

const FRect& Hitbox::get_bounds() const noexcept {
  return bounds;
}

bool Hitbox::is_unit() const noexcept {
  return rectangles.size() == 1;
}

bool Hitbox::is_enabled() const noexcept {
  return enabled;
}

}
