#pragma once

namespace albinjohansson::wanderer {

/**
 * The Vector2 class represents a floating-point two-dimensional vector. This class is inspired
 * by the libGDX class with the same name.
 *
 * <a href=
 * https://libgdx.badlogicgames.com/ci/nightlies/docs/api/com/badlogic/gdx/math/Vector2.html>
 * The libGDX Vector2 class</a>
 * @see
 * @since 0.1.0
 */
class Vector2 final {
 public:
  float x = 0;
  float y = 0;

  /**
   * Creates a vector with coordinates (0, 0).
   *
   * @since 0.1.0
   */
  Vector2();

  /**
   * @param x the x-coordinate of the vector.
   * @param y the y-coordinate of the vector.
   * @since 0.1.0
   */
  Vector2(float x, float y);

  /**
   * Creates a copy of the supplied vector.
   *
   * @param vector the vector that will be copied.
   * @since 0.1.0
   */
  Vector2(const Vector2& vector);

  // TODO dot multiplication, angle stuff (rotation)

  /**
   * Scales the vector. The supplied factor is multiplied with both of the coordinates of the
   * vector.
   *
   * @param factor the factor that is used when scaling the vector.
   * @since 0.1.0
   */
  void Scale(float factor) noexcept;

  /**
   * Normalizes the vector. The vector will have length 1 after invoking this method.
   *
   * @since 0.1.0
   */
  void Norm() noexcept;

  /**
   * Linearly interpolates between this vector and the specified target vector. This vector is
   * the one that is affected by the operation.
   *
   * @param target the target vector.
   * @param alpha the interpolation coefficient, in the range [0, 1].
   * @since 0.1.0
   */
  void Lerp(const Vector2& target, float alpha) noexcept;

  /**
   * Interpolates between this vector and the specified target vector, using a special algorithm
   * to achieve a "smoother" alpha coefficient value. This vector is the one that is affected by
   * the operation.
   *
   * @param target the target vector.
   * @param alpha the interpolation coefficient, in the range [0, 1].
   * @since 0.1.0
   */
  void Interpolate(const Vector2& target, float alpha) noexcept;

  Vector2 operator+(const Vector2& v) const noexcept;

  Vector2 operator-(const Vector2& v) const noexcept;

  bool operator==(const Vector2& v) const noexcept;

  bool operator!=(const Vector2& v) const noexcept;

//  Vector2 operator^(float exp) const noexcept;

  /**
   * Adds the coordinates of the supplied vector to the vector. The invoked vector is the one
   * that is affected by the operation.
   *
   * @param vector the vector that will be added to this vector.
   * @since 0.1.0
   */
  void Add(const Vector2& vector) noexcept;

  /**
   * Adds the supplied offsets to the coordinates of the vector.
   *
   * @param x the x-axis value that will be added to the current x-coordinate.
   * @param y the y-axis value that will be added to the current y-coordinate.
   * @since 0.1.0
   */
  void Add(float x, float y) noexcept;

  /**
   * Subtracts the coordinates of the supplied vector from the vector. The invoked vector is the one
   * that is affected by the operation.
   *
   * @param vector the vector that will be subtracted to this vector.
   * @since 0.1.0
   */
  void Sub(const Vector2& vector) noexcept;

  /**
   * Adopts the values of the supplied vector.
   *
   * @param vector the vector whose values will be adopted.
   * @since 0.1.0
   */
  void Set(const Vector2& vector) noexcept;

  /**
   * Sets the total length of the vector.
   *
   * @param length the new length of the vector.
   * @since 0.1.0
   */
  void SetLength(float length) noexcept;

  /**
   * Makes the vector point at the target vector. The magnitude of the vector will remain unchanged
   * after invoking this method.
   *
   * @param target the target vector.
   * @since 0.1.0
   */
  void LookAt(const Vector2& target) noexcept;

  /**
   * Makes the vector point at the target vector. The supplied length value will be the new
   * magnitude of the vector after invoking this method.
   *
   * @param target the target vector.
   * @param length the magnitude of the vector after performing the transformation, will be
   * clamped to zero if negative.
   * @since 0.1.0
   */
  void LookAt(const Vector2& target, float length) noexcept;

  /**
   * Returns the distance between the vector and the supplied vector.
   *
   * @param vector the vector to calculate the distance to.
   * @return the distance between the vector and the supplied vector.
   * @since 0.1.0
   */
  [[nodiscard]] float DistanceTo(const Vector2& vector) const noexcept;

  /**
   * Returns the squared distance between the vector and the supplied vector.
   *
   * @param vector the vector to calculate the distance to.
   * @return the squared distance between the vector and the supplied vector.
   * @since 0.1.0
   */
  [[nodiscard]] float DistanceTo2(const Vector2& vector) const noexcept;

  /**
   * Returns the integer representation of the x-coordinate of the vector.
   *
   * @return the x-coordinate of the vector.
   * @since 0.1.0
   */
  [[nodiscard]] int GetX() const noexcept { return static_cast<int>(x); }

  /**
   * Returns the the integer representation of the y-coordinate of the vector.
   *
   * @return the y-coordinate of the vector.
   * @since 0.1.0
   */
  [[nodiscard]] int GetY() const noexcept { return static_cast<int>(y); }

  /**
   * Calculates and returns the length of the vector.
   *
   * @return the length of the vector.
   * @since 0.1.0
   */
  [[nodiscard]] float GetLength() const noexcept;

  /**
   * Calculates and returns the squared length of the vector. This method is useful when
   * comparing the length of two vectors, where the square roots doesn't have to be computed.
   * This method is slightly faster than the ordinary GetLength method.
   *
   * @return the squared length of the vector.
   * @since 0.1.0
   */
  [[nodiscard]] float GetLength2() const noexcept;

  /**
   * Indicates whether or not the vector is the zero vector.
   *
   * @return true if all coordinates are zero; false otherwise.
   * @since 0.1.0
   */
  [[nodiscard]] bool IsZero() const noexcept;

  /**
   * Indicates whether or not the vector is a unit vector (a vector with length 1).
   *
   * @return true if the vector is a unit vector; false otherwise.
   * @since 0.1.0
   */
  [[nodiscard]] bool IsUnit() const noexcept;
};

}
