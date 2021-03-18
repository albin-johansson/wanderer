#include "hitbox_system.hpp"

#include <algorithm>  // min, max

#include "centurion_utils.hpp"

namespace wanderer::sys {
namespace {

[[nodiscard]] auto next_vertical_hitbox(const comp::movable& movable,
                                        const comp::hitbox& hitbox,
                                        const float2& oldPosition,
                                        const delta_t dt) -> maybe<comp::hitbox>
{
  if (movable.velocity.y != 0)
  {
    auto next = oldPosition;
    next.y = oldPosition.y + (movable.velocity.y * dt);

    return with_position(hitbox, next);
  }
  else
  {
    return std::nullopt;
  }
}

[[nodiscard]] auto next_horizontal_hitbox(const comp::movable& movable,
                                          const comp::hitbox& hitbox,
                                          const float2& oldPosition,
                                          const delta_t dt)
    -> maybe<comp::hitbox>
{
  if (movable.velocity.x != 0)
  {
    auto next = oldPosition;
    next.x = oldPosition.x + (movable.velocity.x * dt);

    return with_position(hitbox, next);
  }
  else
  {
    return std::nullopt;
  }
}

}  // namespace

void update_bounds(comp::hitbox& hitbox) noexcept
{
  if (hitbox.boxes.empty())
  {
    return;
  }

  float x{};
  float y{};
  float mx{};
  float my{};

  bool first{true};
  for (const auto& [offset, size] : hitbox.boxes)
  {
    if (first)
    {
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

void set_position(comp::hitbox& hitbox, const float2& position) noexcept
{
  hitbox.origin = position;
  update_bounds(hitbox);
}

auto with_position(const comp::hitbox& hitbox, const float2& position) noexcept
    -> comp::hitbox
{
  auto result = hitbox;
  set_position(result, position);
  return result;
}

auto intersects(const comp::hitbox& fst, const comp::hitbox& snd) noexcept
    -> bool
{
  if (&fst == &snd)
  {
    return false;
  }

  if (!cen::intersects(fst.bounds, snd.bounds))
  {
    // Cannot intersect if the bounding rectangles don't intersect
    return false;
  }

  if (!fst.enabled || !snd.enabled)
  {
    // Cannot intersect if either hitbox isn't enabled
    return false;
  }

  for (const auto& [fstOffset, fstSize] : fst.boxes)
  {
    const cen::frect rectA{to_point(fst.origin + fstOffset), fstSize};

    for (const auto& [sndOffset, sndSize] : snd.boxes)
    {
      const cen::frect rectB{to_point(snd.origin + sndOffset), sndSize};

      if (cen::collides(rectA, rectB))
      {
        return true;
      }
    }
  }

  return false;
}

auto create_hitbox(std::initializer_list<comp::subhitbox> boxes) -> comp::hitbox
{
  comp::hitbox hb;

  hb.boxes.reserve(boxes.size());
  for (const auto& box : boxes)
  {
    hb.boxes.push_back(box);
  }

  set_position(hb, {});

  return hb;
}

auto make_next_hitboxes(const comp::movable& movable,
                        const comp::hitbox& hitbox,
                        const float2& oldPosition,
                        const delta_t dt) -> next_hitboxes
{
  return {next_horizontal_hitbox(movable, hitbox, oldPosition, dt),
          next_vertical_hitbox(movable, hitbox, oldPosition, dt)};
}

auto query_collisions(const next_hitboxes& next, const comp::hitbox& other)
    -> collision_result
{
  collision_result result;

  result.horizontal = next.horizontal && intersects(*next.horizontal, other);
  result.vertical = next.vertical && intersects(*next.vertical, other);

  return result;
}

}  // namespace wanderer::sys
