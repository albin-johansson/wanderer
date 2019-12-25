#pragma once
#include "f_rectangle.h"
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
  FRectangle bounds;
  std::vector<std::pair<FRectangle, Vector2>> rectangles;
  bool enabled = false;

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
  void AddRectangle(const FRectangle& rect, const Vector2& offset);

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
   * Sets whether or not the hitbox is enabled. A hitbox that is disabled cannot intersect other
   * hitboxes.
   *
   * @param enabled true if the hitbox should be enabled; false otherwise.
   * @since 0.1.0
   */
  void SetEnabled(bool enabled) noexcept;

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

  [[nodiscard]] bool Intersects(const FRectangle& other) const noexcept;

  [[nodiscard]] bool WillIntersect(const Hitbox& other, const Vector2& nextPos) const noexcept;

  /**
   * Indicates whether or not the hitbox is enabled.
   *
   * @return true if the hitbox is enabled; false otherwise.
   * @since 0.1.0
   */
  [[nodiscard]] bool IsEnabled() const noexcept;

  /**
   * Returns the rectangle that represents the bounds of the hitbox.
   *
   * @return the rectangle that represents the bounds of the hitbox.
   * @since 0.1.0
   */
  [[nodiscard]] const FRectangle& GetBounds() const noexcept;
};

}
