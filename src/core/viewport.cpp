#include "viewport.h"

#include <stdexcept>

using namespace centurion;

namespace wanderer {

Viewport::Viewport() : Viewport{{10, 10}, {10, 10}}
{}

Viewport::Viewport(Area viewport, Area level) : m_level(level)
{
  if (viewport.width < 1 || viewport.height < 1 || level.width < 1 ||
      level.height < 1) {
    throw std::invalid_argument("Invalid dimensions!");
  }
  m_bounds.set_width(viewport.width);
  m_bounds.set_height(viewport.height);
}

void Viewport::track(float tx, float ty, Area size, float delta) noexcept
{
  const float panSpeed = 15.0f * delta;

  const float targetX = (tx + (size.width / 2.0f)) - (m_bounds.width() / 2.0f);
  const float targetY =
      (ty + (size.height / 2.0f)) - (m_bounds.height() / 2.0f);
  float x = m_bounds.x() + (targetX - m_bounds.x()) * panSpeed;
  float y = m_bounds.y() + (targetY - m_bounds.y()) * panSpeed;

  if (x < 0) {
    x = 0;
  }

  if (y < 0) {
    y = 0;
  }

  const float widthDiff = m_level.width - m_bounds.width();
  x = (x > widthDiff) ? widthDiff : x;

  const float heightDiff = m_level.height - m_bounds.height();
  y = (y > heightDiff) ? heightDiff : y;

  m_bounds.set_x(x);
  m_bounds.set_y(y);
}

void Viewport::center(float tx, float ty, Area size) noexcept
{
  float x = (tx + (size.width / 2.0f)) - (m_bounds.width() / 2.0f);
  float y = (ty + (size.height / 2.0f)) - (m_bounds.height() / 2.0f);

  if (x < 0) {
    x = 0;
  }

  if (y < 0) {
    y = 0;
  }

  const float widthDiff = m_level.width - m_bounds.width();
  x = (x > widthDiff) ? widthDiff : x;

  const float heightDiff = m_level.height - m_bounds.height();
  y = (y > heightDiff) ? heightDiff : y;

  m_bounds.set_x(x);
  m_bounds.set_y(y);
}

void Viewport::set_x(float x) noexcept
{
  m_bounds.set_x(x);
}

void Viewport::set_y(float y) noexcept
{
  m_bounds.set_y(y);
}

void Viewport::set_width(float width)
{
  m_bounds.set_width(width);
}

void Viewport::set_height(float height)
{
  m_bounds.set_height(height);
}

void Viewport::set_level_width(float levelWidth)
{
  if (levelWidth <= 0) {
    throw std::invalid_argument("Invalid level width!");
  } else {
    m_level.width = levelWidth;
  }
}

void Viewport::set_level_height(float levelHeight)
{
  if (levelHeight <= 0) {
    throw std::invalid_argument("Invalid level height!");
  } else {
    m_level.height = levelHeight;
  }
}

const FRect& Viewport::get_bounds() const noexcept
{
  return m_bounds;
}

float Viewport::get_translated_x(float x) const noexcept
{
  return x - m_bounds.x();
}

float Viewport::get_translated_y(float y) const noexcept
{
  return y - m_bounds.y();
}

}  // namespace wanderer
