#pragma once
#include "rectangle.h"
#include <vector>

namespace albinjohansson::wanderer {

/**
 * The Hitbox class represents a hitbox built from rectangles.
 *
 * @since 0.1.0
 */
class Hitbox final {
 private:
  Rectangle bounds;
  std::vector<Rectangle> rectangles;

  void CalcBounds();

 public:
  Hitbox();

  ~Hitbox();

  /**
   * Adds a rectangle that will serve as a part of the hitbox.
   *
   * @param rect a rectangle that will serve as a part of the hitbox.
   * @since 0.1.0
   */
  void AddRectangle(const Rectangle& rect);

  /**
   * Indicates whether or not the supplied hitbox intersects this hitbox.
   *
   * @param other the other hitbox to check.
   * @return true if the hitboxes intersect; false otherwise.
   * @since 0.1.0
   */
  [[nodiscard]] bool Intersects(const Hitbox& other) const noexcept;

  [[nodiscard]] const Rectangle& GetBounds() const noexcept { return bounds; } // FIXME remove temp
};

}
