#pragma once

namespace wanderer::core {

/**
 * The Rectangle class represents a rectangle with floating-point coordinates and integer
 * dimensions.
 *
 * @since 0.1.0
 */
class Rectangle final {
 private:
  float x;
  float y;
  int width;
  int height;

 public:
  /**
   * Creates a 10x10 rectangle located at (0, 0).
   *
   * @since 0.1.0
   */
  Rectangle() noexcept;

  /**
   * @param x the x-coordinate of the rectangle.
   * @param y the y-coordinate of the rectangle.
   * @param width the width of the rectangle.
   * @param height the height of the rectangle.
   * @since 0.1.0
   */
  Rectangle(float x, float y, int width, int height) noexcept;

  /**
   * Creates a copy of the supplied rectangle.
   *
   * @param rectangle the rectangle that will be copied.
   * @since 0.1.0
   */
  Rectangle(const Rectangle& rectangle) noexcept;

  /**
   * Moves the rectangle by the specified amount along the x-axis.
   *
   * @param dx the x-axis offset, may be negative.
   * @since 0.1.0
   */
  void MoveX(float dx) noexcept;

  /**
   * Moves the rectangle by the specified amount along the y-axis.
   *
   * @param dy the y-axis offset, may be negative.
   * @since 0.1.0
   */
  void MoveY(float dy) noexcept;

  /**
   * Sets the x-coordinate of the rectangle.
   *
   * @param x the new x-coordinate of the rectangle.
   * @since 0.1.0
   */
  void SetX(float x) noexcept;

  /**
   * Sets the y-coordinate of the rectangle.
   *
   * @param x the new y-coordinate of the rectangle.
   * @since 0.1.0
   */
  void SetY(float y) noexcept;

  /**
   * Sets the width of the rectangle.
   *
   * @param x the new width of the rectangle.
   * @since 0.1.0
   */
  void SetWidth(int width) noexcept;

  /**
   * Sets the height of the rectangle.
   *
   * @param x the new height of the rectangle.
   * @since 0.1.0
   */
  void SetHeight(int height) noexcept;

  /**
   * Indicates whether or not the rectangle contains the point represented by the supplied
   * coordinates.
   *
   * @param px the x-coordinate of the point that will be checked.
   * @param py the y-coordinate of the point that will be checked.
   * @return true if the supplied point is contained in the rectangle; false otherwise.
   */
  [[nodiscard]] bool Contains(float px, float py) const noexcept;

  /**
   * Indicates whether or not the rectangle intersects the supplied rectangle.
   *
   * @param rectangle the rectangle to check for an intersection.
   * @return true if the rectangle intersects the supplied rectangle; false otherwise.
   * @since 0.1.0
   */
  [[nodiscard]] bool Intersects(const Rectangle& rectangle) const noexcept;

  /**
   * Returns the x-coordinate of the rectangle.
   *
   * @return the x-coordinate of the rectangle.
   * @since 0.1.0
   */
  [[nodiscard]] inline float GetX() const noexcept { return x; }

  /**
   * Returns the y-coordinate of the rectangle.
   *
   * @return the y-coordinate of the rectangle.
   * @since 0.1.0
   */
  [[nodiscard]] inline float GetY() const noexcept { return y; }

  /**
   * Returns the width of the rectangle.
   *
   * @return the width of the rectangle.
   * @since 0.1.0
   */
  [[nodiscard]] inline int GetWidth() const noexcept { return width; }

  /**
   * Returns the height of the rectangle.
   *
   * @return the height of the rectangle.
   * @since 0.1.0
   */
  [[nodiscard]] inline int GetHeight() const noexcept { return height; }

  /**
   * Returns the maximum x-coordinate of the rectangle.
   *
   * @return the maximum x-coordinate.
   * @since 0.1.0
   */
  [[nodiscard]] inline float GetMaxX() const noexcept { return x + static_cast<float>(width); }

  /**
   * Returns the maximum y-coordinate of the rectangle.
   *
   * @return the maximum y-coordinate.
   * @since 0.1.0
   */
  [[nodiscard]] inline float GetMaxY() const noexcept { return y + static_cast<float>(height); }

};

}
