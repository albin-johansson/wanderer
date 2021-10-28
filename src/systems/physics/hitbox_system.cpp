#include "hitbox_system.hpp"

#include <algorithm>  // min, max

#include "core/utils/centurion_utils.hpp"

namespace wanderer::sys {
namespace {

[[nodiscard]] auto NextVerticalHitbox(const comp::Hitbox& hitbox,
                                      const float2& position,
                                      const float2& velocity,
                                      const float dt) -> maybe<comp::Hitbox>
{
  if (velocity.y != 0) {
    auto next = position;
    next.y = position.y + (velocity.y * dt);
    return WithPosition(hitbox, next);
  }
  else {
    return std::nullopt;
  }
}

[[nodiscard]] auto NextHorizontalHitbox(const comp::Hitbox& hitbox,
                                        const float2& position,
                                        const float2& velocity,
                                        const float dt) -> maybe<comp::Hitbox>
{
  if (velocity.x != 0) {
    auto next = position;
    next.x = position.x + (velocity.x * dt);
    return WithPosition(hitbox, next);
  }
  else {
    return std::nullopt;
  }
}

}  // namespace

void UpdateBounds(comp::Hitbox& hitbox)
{
  if (hitbox.boxes.empty()) {
    return;
  }

  float x{};
  float y{};
  float mx{};
  float my{};

  bool first = true;
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

void SetPosition(comp::Hitbox& hitbox, float2 position)
{
  hitbox.origin = position;
  UpdateBounds(hitbox);
}

auto WithPosition(const comp::Hitbox& hitbox, float2 position) -> comp::Hitbox
{
  auto result = hitbox;
  SetPosition(result, position);
  return result;
}

auto Intersects(const comp::Hitbox& fst, const comp::Hitbox& snd) -> bool
{
  // 1. A hitbox doesn't intersect itself
  // 2. The hitboxes can't intersect if their bounding rectangles don't intersect
  // 3. The hitboxes can't intersect unless both are enabled
  if (&fst == &snd || !cen::intersects(fst.bounds, snd.bounds) || !fst.enabled ||
      !snd.enabled)
  {
    return false;
  }

  for (const auto& [fstOffset, fstSize] : fst.boxes) {
    const auto fstRect = cen::frect{to_point(fst.origin + fstOffset), fstSize};

    for (const auto& [sndOffset, sndSize] : snd.boxes) {
      const auto sndRect = cen::frect{to_point(snd.origin + sndOffset), sndSize};

      if (cen::collides(fstRect, sndRect)) {
        return true;
      }
    }
  }

  return false;
}

auto MakeHitbox(std::initializer_list<comp::Subhitbox> boxes) -> comp::Hitbox
{
  comp::Hitbox hb;

  for (const auto& box : boxes) {
    hb.boxes.push_back(box);
  }

  SetPosition(hb, {});

  return hb;
}

auto MakeNextHitboxes(const comp::Movable& movable,
                      const comp::Hitbox& hitbox,
                      float2 oldPosition,
                      float dt) -> NextHitboxes
{
  return {NextHorizontalHitbox(hitbox, oldPosition, movable.velocity, dt),
          NextVerticalHitbox(hitbox, oldPosition, movable.velocity, dt)};
}

auto QueryCollisions(const NextHitboxes& next, const comp::Hitbox& obstacle)
    -> CollisionResult
{
  CollisionResult result;

  result.horizontal = next.horizontal && Intersects(*next.horizontal, obstacle);
  result.vertical = next.vertical && Intersects(*next.vertical, obstacle);

  return result;
}

}  // namespace wanderer::sys
