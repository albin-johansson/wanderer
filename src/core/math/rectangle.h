#pragma once
#include <SDL.h>

namespace albinjohansson::wanderer {

class Rectangle final {
 private:
  int x = 0;
  int y = 0;
  int width = 0;
  int height = 0;

 public:
  Rectangle();

  Rectangle(int x, int y, int width, int height);

  Rectangle(const Rectangle& other);

  ~Rectangle() noexcept;

  /**
   * Moves the rectangle by the specified amount along the x-axis.
   *
   * @param dx the x-axis offset, may be negative.
   * @since 0.1.0
   */
  void MoveX(int dx) noexcept;

  /**
   * Moves the rectangle by the specified amount along the y-axis.
   *
   * @param dy the y-axis offset, may be negative.
   * @since 0.1.0
   */
  void MoveY(int dy) noexcept;

  /**
   * Copies all of the values from the other rectangle to this rectangle.
   *
   * @param other the rectangle that will be copied.
   * @since 0.1.0
   */
  void Set(const Rectangle& other) noexcept;

  /**
   * Sets the x-coordinate of the rectangle.
   *
   * @param x the new x-coordinate of the rectangle.
   * @since 0.1.0
   */
  void SetX(int x) noexcept;

  /**
   * Sets the y-coordinate of the rectangle.
   *
   * @param x the new y-coordinate of the rectangle.
   * @since 0.1.0
   */
  void SetY(int y) noexcept;

  /**
   * Sets the width of the rectangle.
   *
   * @param x the new width of the rectangle.
   * @throws invalid_argument if the supplied width isn't greater than zero.
   * @since 0.1.0
   */
  void SetWidth(int width);

  /**
   * Sets the height of the rectangle.
   *
   * @param x the new height of the rectangle.
   * @throws invalid_argument if the supplied width isn't greater than zero.
   * @since 0.1.0
   */
  void SetHeight(int height);

  /**
   * Indicates whether or not the rectangle contains the point represented by the supplied
   * coordinates.
   *
   * @param px the x-coordinate of the point that will be checked.
   * @param py the y-coordinate of the point that will be checked.
   * @return true if the supplied point is contained in the rectangle; false otherwise.
   */
  [[nodiscard]] bool Contains(int px, int py) const noexcept;

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
  [[nodiscard]] int GetX() const noexcept;

  /**
   * Returns the y-coordinate of the rectangle.
   *
   * @return the y-coordinate of the rectangle.
   * @since 0.1.0
   */
  [[nodiscard]] int GetY() const noexcept;

  /**
   * Returns the width of the rectangle.
   *
   * @return the width of the rectangle.
   * @since 0.1.0
   */
  [[nodiscard]] int GetWidth() const noexcept;

  /**
   * Returns the height of the rectangle.
   *
   * @return the height of the rectangle.
   * @since 0.1.0
   */
  [[nodiscard]] int GetHeight() const noexcept;

  [[nodiscard]] int GetCenterX() const noexcept;

  [[nodiscard]] int GetCenterY() const noexcept;

  /**
   * Returns the maximum x-coordinate of the rectangle.
   *
   * @return the maximum x-coordinate.
   * @since 0.1.0
   */
  [[nodiscard]] int GetMaxX() const noexcept;

  /**
   * Returns the maximum y-coordinate of the rectangle.
   *
   * @return the maximum y-coordinate.
   * @since 0.1.0
   */
  [[nodiscard]] int GetMaxY() const noexcept;

  /**
   * Returns an SDL_Rect representation of the rectangle.
   *
   * @return an SDL_Rect representation of the rectangle.
   * @since 0.1.0
   */
  [[nodiscard]] SDL_Rect ToSdlRect() const noexcept;
};

}
