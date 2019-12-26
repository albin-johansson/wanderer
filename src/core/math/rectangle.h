#pragma once
#include <SDL.h>

namespace albinjohansson::wanderer {

class FRectangle;

class Rectangle final {
 private:
  int x = 0;
  int y = 0;
  int width = 0;
  int height = 0;

 public:
  Rectangle();

  Rectangle(int x, int y, int width, int height);

  Rectangle(SDL_Rect rect);

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

  explicit operator FRectangle() const noexcept;

  operator SDL_Rect() const noexcept;

  explicit operator SDL_FRect() const noexcept;
};

/**
 * The Rectangle class represents a rectangle with floating-point coordinates and integer
 * dimensions.
 *
 * @since 0.1.0
 */
class FRectangle final {
 private:
  float x;
  float y;
  float width;
  float height;

 public:
  /**
   * Creates a 10x10 rectangle located at (0, 0).
   *
   * @since 0.1.0
   */
  FRectangle() noexcept;

  /**
   * @param x the x-coordinate of the rectangle.
   * @param y the y-coordinate of the rectangle.
   * @param width the width of the rectangle.
   * @param height the height of the rectangle.
   * @throws invalid_argument if either the width or height isn't greater than zero.
   * @since 0.1.0
   */
  FRectangle(float x, float y, float width, float height); // TODO use Area struct

  FRectangle(SDL_FRect rect);

  FRectangle(SDL_Rect rect);

  /**
   * Creates a copy of the supplied rectangle.
   *
   * @param rectangle the rectangle that will be copied.
   * @since 0.1.0
   */
  FRectangle(const FRectangle& rectangle) noexcept;

  ~FRectangle() = default;

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
   * Copies all of the values from the other rectangle to this rectangle.
   *
   * @param other the rectangle that will be copied.
   * @since 0.1.0
   */
  void Set(const FRectangle& other) noexcept;

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
   * @throws invalid_argument if the supplied width isn't greater than zero.
   * @since 0.1.0
   */
  void SetWidth(float width);

  /**
   * Sets the height of the rectangle.
   *
   * @param x the new height of the rectangle.
   * @throws invalid_argument if the supplied width isn't greater than zero.
   * @since 0.1.0
   */
  void SetHeight(float height);

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
  [[nodiscard]] bool Intersects(const FRectangle& rectangle) const noexcept;

  /**
   * Returns the x-coordinate of the rectangle.
   *
   * @return the x-coordinate of the rectangle.
   * @since 0.1.0
   */
  [[nodiscard]] float GetX() const noexcept;

  /**
   * Returns the y-coordinate of the rectangle.
   *
   * @return the y-coordinate of the rectangle.
   * @since 0.1.0
   */
  [[nodiscard]] float GetY() const noexcept;

  /**
   * Returns the width of the rectangle.
   *
   * @return the width of the rectangle.
   * @since 0.1.0
   */
  [[nodiscard]] float GetWidth() const noexcept;

  /**
   * Returns the height of the rectangle.
   *
   * @return the height of the rectangle.
   * @since 0.1.0
   */
  [[nodiscard]] float GetHeight() const noexcept;

  [[nodiscard]] float GetCenterX() const noexcept;

  [[nodiscard]] float GetCenterY() const noexcept;

  /**
   * Returns the maximum x-coordinate of the rectangle.
   *
   * @return the maximum x-coordinate.
   * @since 0.1.0
   */
  [[nodiscard]] float GetMaxX() const noexcept;

  /**
   * Returns the maximum y-coordinate of the rectangle.
   *
   * @return the maximum y-coordinate.
   * @since 0.1.0
   */
  [[nodiscard]] float GetMaxY() const noexcept;

  explicit operator Rectangle() const noexcept;

  explicit operator SDL_Rect() const noexcept;

  operator SDL_FRect() const noexcept;
};

}