#pragma once
#include "rectangle.h"
#include "vector_2.h"
#include <vector>
#include <utility>

namespace albinjohansson::wanderer {

/**
 * The Hitbox class represents a hitbox built from rectangles.
 *
 * @since 0.1.0
 */
class Hitbox final {
 private:
  Rectangle bounds;
  std::vector<std::pair<Rectangle, Vector2>> rectangles;

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
   * Sets the x-coordinate of the hitbox.
   *
   * @param x the new x-coordinate of the hitbox.
   * @since 0.1.0
   */
  void SetX(float x) noexcept;

  /**
   * Sets the y-coordinate of the hitbox.
   *
   * @param y the new y-coordinate of the hitbox.
   * @since 0.1.0
   */
  void SetY(float y) noexcept;

  /**
   * Returns the total amount of subhitboxes.
   *
   * @return the total amount of subhitboxes.
   * @since 0.1.0
   */
  [[nodiscard]] int GetSubhitboxAmount() const noexcept;

  /**
   * Indicates whether or not the hitbox only contains one rectangle.
   *
   * @return true if the hitbox is built by only one rectangle; false otherwise.
   * @since 0.1.0
   */
  [[nodiscard]] bool IsUnit() const noexcept;

  /**
   * Indicates whether or not the supplied hitbox intersects this hitbox.
   *
   * @param other the other hitbox to check.
   * @return true if the hitboxes intersect; false otherwise.
   * @since 0.1.0
   */
  [[nodiscard]] bool Intersects(const Hitbox& other) const noexcept;

  [[nodiscard]] bool Intersects(const Rectangle& other) const noexcept;

  [[nodiscard]] const Rectangle& GetBounds() const noexcept;
};

}
