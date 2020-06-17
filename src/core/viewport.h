#pragma once
#include <rect.h>

#include "vector_2.h"
#include "wanderer_stdinc.h"

namespace wanderer {

class Viewport final {
 public:
  /**
   * Tracks the viewport towards the entity with the specified properties.
   *
   * @param targetPosComp the position that will be targeted.
   * @param boundsPosComp the size of the target entity.
   * @param delta the delta time, in seconds.
   */
  void track(const Vector2f& target, const centurion::FArea& size, Delta delta);

  void center(const Vector2f& target, const centurion::FArea& size);

  void set_x(float x) noexcept;

  void set_y(float y) noexcept;

  void set_bounds(const centurion::FRect& bounds) noexcept;

  void set_level_size(const centurion::FArea& levelSize) noexcept;

  [[nodiscard]] const centurion::FRect& bounds() const noexcept
  {
    return m_bounds;
  }

  [[nodiscard]] const centurion::FArea& level_size() const noexcept
  {
    return m_levelSize;
  }

 private:
  centurion::FRect m_bounds{};
  centurion::FArea m_levelSize{};
};

}  // namespace wanderer
