#include "viewport.h"

using namespace centurion;

namespace wanderer {

void Viewport::track(const Vector2f& position,
                     const FArea& size,
                     const float delta)
{
  const auto panSpeed = 15.0f * delta;

  const float targetX =
      (position.x + (size.width / 2.0f)) - (m_bounds.width() / 2.0f);

  const float targetY =
      (position.y + (size.height / 2.0f)) - (m_bounds.height() / 2.0f);

  const auto calc = [&](float targetPosComp,
                        float boundsPosComp,
                        float levelSizeComp,
                        float boundsSizeComp) noexcept -> float {
    float value = boundsPosComp + (targetPosComp - boundsPosComp) * panSpeed;
    if (value < 0) {
      value = 0;
    }
    const float diff = levelSizeComp - boundsSizeComp;
    value = (value > diff) ? diff : value;
    return value;
  };

  m_bounds.set_x(
      calc(targetX, m_bounds.x(), m_levelSize.width, m_bounds.width()));
  m_bounds.set_y(
      calc(targetY, m_bounds.y(), m_levelSize.height, m_bounds.height()));
}

// void Viewport::center()
//{
//  // TODO implement
//}

void Viewport::set_x(const float x) noexcept
{
  m_bounds.set_x(x);
}

void Viewport::set_y(const float y) noexcept
{
  m_bounds.set_y(y);
}

void Viewport::set_bounds(const FRect& bounds) noexcept
{
  m_bounds = bounds;
}

void Viewport::set_level_size(const FArea& levelSize) noexcept
{
  m_levelSize = levelSize;
}

}  // namespace wanderer
