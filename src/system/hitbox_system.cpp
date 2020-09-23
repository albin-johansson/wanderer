#include "hitbox_system.hpp"

namespace wanderer::sys::hitbox {

void update_bounds(comp::hitbox& hitbox) noexcept
{
  bool first = true;
  for (auto& [offset, rect] : hitbox.boxes) {
    if (first) {
      hitbox.bounds = rect;
      first = false;
    }

    const auto rectX = rect.x();
    const auto rectY = rect.y();
    const auto rectMaxX = rect.max_x();
    const auto rectMaxY = rect.max_y();

    auto& bounds = hitbox.bounds;

    if (rectX < bounds.x()) {
      bounds.set_x(rectX);
    }

    if (rectY < bounds.y()) {
      bounds.set_y(rectY);
    }

    if (rectMaxX > bounds.max_x()) {
      bounds.set_width(rectMaxX - bounds.x());
    }

    if (rectMaxY > bounds.max_y()) {
      bounds.set_height(rectMaxY - bounds.y());
    }

    offset.set_x(rectX - hitbox.bounds.x());
    offset.set_y(rectY - hitbox.bounds.y());
  }
}

void update_position(comp::hitbox& hitbox, const vector2f& position) noexcept
{
  for (auto& [offset, rect] : hitbox.boxes) {
    const auto x = position.x() + offset.x();
    const auto y = position.y() + offset.y();
    rect.set_x(x);
    rect.set_y(y);
  }
  hitbox.bounds.set_x(position.x());
  hitbox.bounds.set_y(position.y());
}

auto intersects(const comp::hitbox& fst, const comp::hitbox& snd) noexcept
    -> bool
{
  if (&fst == &snd) {
    return false;
  }

  if (!cen::intersects(fst.bounds, snd.bounds)) {
    // Cannot intersect if the bounding rectangles don't intersect
    return false;
  }

  for (const auto& [x, fstRect] : fst.boxes) {
    for (const auto& [x, sndRect] : snd.boxes) {
      if (cen::intersects(fstRect, sndRect)) {
        return true;
      }
    }
  }

  return false;
}

}  // namespace wanderer::sys::hitbox
