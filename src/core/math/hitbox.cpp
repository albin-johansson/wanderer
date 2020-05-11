#include "hitbox.h"

using namespace centurion;

namespace albinjohansson::wanderer {

Hitbox::Hitbox() = default;

Hitbox::~Hitbox() = default;

void Hitbox::calc_bounds()
{
  bool first = true;

  for (auto& [rect, offset] : m_rectangles) {
    if (first) {
      m_bounds.set(rect);
      first = false;
    }

    const auto rectX = rect.x();
    const auto rectY = rect.y();
    const auto rectMaxX = rect.max_x();
    const auto rectMaxY = rect.max_y();

    if (rectX < m_bounds.x()) {
      m_bounds.set_x(rectX);
    }

    if (rectY < m_bounds.y()) {
      m_bounds.set_y(rectY);
    }

    if (rectMaxX > m_bounds.max_x()) {
      m_bounds.set_width(rectMaxX - m_bounds.x());
    }

    if (rectMaxY > m_bounds.max_y()) {
      m_bounds.set_height(rectMaxY - m_bounds.y());
    }

    offset.x = rectX - m_bounds.x();
    offset.y = rectY - m_bounds.y();
  }
}

void Hitbox::add_rectangle(const FRect& rect, const Vector2& offset)
{
  m_rectangles.emplace_back(rect, offset);
  calc_bounds();
}

void Hitbox::set_x(float x) noexcept
{
  m_bounds.set_x(x);
  for (auto& [rect, offset] : m_rectangles) {
    rect.set_x(x + offset.x);
  }
}

void Hitbox::set_y(float y) noexcept
{
  m_bounds.set_y(y);
  for (auto& [rect, offset] : m_rectangles) {
    rect.set_y(y + offset.y);
  }
}

void Hitbox::set_enabled(bool enabled) noexcept
{
  this->m_enabled = enabled;
}

bool Hitbox::intersects(const Hitbox& other) const noexcept
{
  if (!m_enabled || &other == this) {
    return false;
  }

  if (other.is_unit()) {
    return intersects(other.m_rectangles.front().first);
  }

  for (const auto& [rect, offset] : m_rectangles) {
    for (const auto& [otherRect, otherOffset] : other.m_rectangles) {
      if (rect.intersects(otherRect)) {
        return true;
      }
    }
  }
  return false;
}

bool Hitbox::intersects(const FRect& other) const noexcept
{
  if (!m_enabled) {
    return false;
  }

  for (const auto& [rect, offset] : m_rectangles) {
    if (rect.intersects(other)) {
      return true;
    }
  }
  return false;
}

bool Hitbox::will_intersect(const Hitbox& other,
                            const Vector2& nextPos) const noexcept
{
  if (!m_enabled) {
    return false;
  }

  const auto oldX = m_bounds.x();
  const auto oldY = m_bounds.y();

  auto tmp = const_cast<Hitbox*>(this);  // FIXME

  tmp->set_x(nextPos.x);
  tmp->set_y(nextPos.y);

  bool intersection = intersects(other);

  tmp->set_x(oldX);
  tmp->set_y(oldY);

  return intersection;
}

const FRect& Hitbox::get_bounds() const noexcept
{
  return m_bounds;
}

bool Hitbox::is_unit() const noexcept
{
  return m_rectangles.size() == 1;
}

bool Hitbox::is_enabled() const noexcept
{
  return m_enabled;
}

}  // namespace albinjohansson::wanderer
