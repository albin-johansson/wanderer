#include "hitbox_system.hpp"

#include <algorithm>  // min, max

#include "centurion_utils.hpp"

namespace wanderer::sys::hitbox {

void update_bounds(comp::hitbox& hitbox) noexcept
{
  if (hitbox.boxes.empty()) {
    return;
  }

  float x{};
  float y{};
  float mx{};
  float my{};

  bool first{true};
  for (const auto& [offset, size] : hitbox.boxes) {
    if (first) {
      x = offset.x;
      y = offset.y;
      mx = x + size.width;
      my = y + size.height;

      hitbox.bounds = {{x, y}, size};
      first = false;
      continue;
    }

    x = std::min(x, offset.x);
    y = std::min(y, offset.y);
    mx = std::max(mx, offset.x + size.width);
    my = std::max(my, offset.y + size.height);
  }

  hitbox.bounds.set_x(hitbox.origin.x + x);
  hitbox.bounds.set_y(hitbox.origin.y + y);
  hitbox.bounds.set_width(mx - x);
  hitbox.bounds.set_height(my - y);
}

void set_position(comp::hitbox& hitbox, const vector2f& position) noexcept
{
  hitbox.origin = position;
  update_bounds(hitbox);
}

auto with_position(const comp::hitbox& hitbox,
                   const vector2f& position) noexcept -> comp::hitbox
{
  auto result = hitbox;
  set_position(result, position);
  return result;
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

  for (const auto& [fstOffset, fstSize] : fst.boxes) {
    const cen::frect rectA{to_point(fst.origin + fstOffset), fstSize};

    for (const auto& [sndOffset, sndSize] : snd.boxes) {
      const cen::frect rectB{to_point(snd.origin + sndOffset), sndSize};

      if (cen::collides(rectA, rectB)) {
        return true;
      }
    }
  }

  return false;
}

auto create(std::initializer_list<comp::subhitbox> boxes) -> comp::hitbox
{
  comp::hitbox hb;

  hb.boxes.reserve(boxes.size());
  for (const auto& box : boxes) {
    hb.boxes.push_back(box);
  }

  set_position(hb, {});

  return hb;
}

}  // namespace wanderer::sys::hitbox
