#pragma once

namespace wanderer::model {

/**
 * The Vector2 class represents a two-dimensional vector that uses integers for its coordinates.
 *
 * @since 0.1.0
 */
class Vector2 final {
 private:
  int x = 0;
  int y = 0;

 public:
  Vector2(int x, int y) noexcept : x(x), y(y) {}

  Vector2(const Vector2& vec) noexcept : Vector2(vec.x, vec.y) {
    x = vec.x;
    y = vec.y;
  }

  ~Vector2() = default;

  /**
   * Adds the coordinates of the supplied vector with the coordinates of this vector.
   *
   * @param vec the vector to add to this vector.
   * @since 0.1.0
   */
  void Add(const Vector2& vec) noexcept;

  /**
   * Subtracts the coordinates of the supplied vector with the coordinates of this vector.
   *
   * @param vec the vector to subtract from this vector.
   * @since 0.1.0
   */
  void Sub(const Vector2& vec) noexcept;

  /**
   * Performs scalar multiplication on the coordinates of the supplied vector with the coordinates
   * of this vector.
   *
   * @param vec the vector used to perform scalar multiplication.
   * @since 0.1.0
   */
  void Mul(const Vector2& vec) noexcept;

  /**
   * Scales the magnitude of the vector.
   *
   * @param factor the factor used when scaling.
   * @since 0.1.0
   */
  void Scale(double factor) noexcept;

  /**
   * Sets the magnitude (length) of the vector.
   *
   * @param mag the new magnitude of the vector.
   * @since 0.1.0
   */
  void SetMagnitude(double mag) noexcept;

  /**
   * Sets the x-coordinate of the vector.
   *
   * @param x the new x-coordinate of the vector.
   * @since 0.1.0
   */
  void SetX(int x) noexcept;

  /**
   * Sets the y-coordinate of the vector.
   *
   * @param y the new y-coordinate of the vector.
   * @since 0.1.0
   */
  void SetY(int y) noexcept;

  /**
   * Returns the magnitude (length) of the vector.
   *
   * @return the magnitude of the vector.
   * @since 0.1.0
   */
  [[nodiscard]]  int GetMagnitude() const noexcept;

  /**
   * Returns the x-coordinate of the vector.
   *
   * @return the x-coordinate of the vector.
   * @since 0.1.0
   */
  [[nodiscard]] inline int GetX() const noexcept {
    return x;
  }

  /**
   * Returns the y-coordinate of the vector.
   *
   * @return the y-coordinate of the vector.
   * @since 0.1.0
   */
  [[nodiscard]] inline int GetY() const noexcept {
    return y;
  }
};

}