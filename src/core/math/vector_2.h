#pragma once
#include "math.h"

namespace albinjohansson::wanderer {

/**
 * The Vector2 class represents a floating-point two-dimensional vector. This
 * class is inspired by the libGDX class with the same name.
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
  constexpr Vector2(float x, float y) : x(x), y(y)
  {}

  /**
   * Creates a copy of the supplied vector.
   *
   * @param other the vector that will be copied.
   * @since 0.1.0
   */
  Vector2(const Vector2& other);

  /**
   * Scales the vector. The supplied factor is multiplied with both of the
   * coordinates of the vector.
   *
   * @param factor the factor that is used when scaling the vector.
   * @since 0.1.0
   */
  void scale(float factor) noexcept;

  /**
   * Normalizes the vector. The vector will have length 1 after invoking this
   * method.
   *
   * @since 0.1.0
   */
  void norm() noexcept;

  /**
   * Sets the components of the vector to be zero.
   *
   * @since 0.1.0
   */
  void zero() noexcept;

  /**
   * Linearly interpolates between this vector and the specified target vector.
   * This vector is the one that is affected by the operation.
   *
   * @param target the target vector.
   * @param alpha the interpolation coefficient, in the range [0, 1].
   * @since 0.1.0
   */
  void lerp(const Vector2& target, float alpha) noexcept;

  /**
   * Interpolates between this vector and the specified target vector, using a
   * special algorithm to achieve a "smoother" alpha coefficient value. This
   * vector is the one that is affected by the operation.
   *
   * @param target the target vector.
   * @param alpha the interpolation coefficient, in the range [0, 1].
   * @since 0.1.0
   */
  void interpolate(const Vector2& target, float alpha) noexcept;

  /**
   * Adds the coordinates of the supplied vector to the vector. The invoked
   * vector is the one that is affected by the operation.
   *
   * @param other the vector that will be added to this vector.
   * @since 0.1.0
   */
  void add(const Vector2& other) noexcept;

  /**
   * Adds the supplied offsets to the coordinates of the vector.
   *
   * @param x the x-axis value that will be added to the current x-coordinate.
   * @param y the y-axis value that will be added to the current y-coordinate.
   * @since 0.1.0
   */
  void add(float x, float y) noexcept;

  /**
   * Subtracts the coordinates of the supplied vector from the vector. The
   * invoked vector is the one that is affected by the operation.
   *
   * @param other the vector that will be subtracted to this vector.
   * @since 0.1.0
   */
  void sub(const Vector2& other) noexcept;

  /**
   * Subtracts the supplied coordinates from the vector.
   *
   * @param x the value that will be subtracted from the x-coordinate of the
   * vector.
   * @param y the value that will be subtracted from the y-coordinate of the
   * vector.
   * @since 0.1.0
   */
  void sub(float x, float y) noexcept;

  /**
   * Adopts the values of the supplied vector.
   *
   * @param other the vector whose values will be adopted.
   * @since 0.1.0
   */
  void set(const Vector2& other) noexcept;

  /**
   * Sets the x- and y-coordinates of the vector.
   *
   * @param x the new x-coordinate.
   * @param y the new y-coordinate.
   * @since 0.1.0
   */
  void set(float x, float y) noexcept;

  /**
   * Sets the total length of the vector.
   *
   * @param length the new length of the vector.
   * @since 0.1.0
   */
  void set_length(float length) noexcept;

  /**
   * Makes the vector point at the target vector. The magnitude of the vector
   * will remain unchanged after invoking this method.
   *
   * @param target the target vector.
   * @since 0.1.0
   */
  void look_at(const Vector2& target) noexcept;

  /**
   * Makes the vector point at the target vector. The supplied length value will
   * be the new magnitude of the vector after invoking this method.
   *
   * @param target the target vector.
   * @param length the magnitude of the vector after performing the
   * transformation, will be clamped to zero if negative.
   * @since 0.1.0
   */
  void look_at(const Vector2& target, float length) noexcept;

  /**
   * Inverts the coordinates of the vector. For example, (4, 8) becomes (-4,
   * -8).
   *
   * @since 0.1.0
   */
  void invert() noexcept;

  /**
   * Returns the result of adding the two vectors.
   *
   * @param other the other vector to add to the first vector.
   * @return the resulting vector of the addition.
   * @since 0.1.0
   */
  [[nodiscard]] Vector2 operator+(const Vector2& other) const noexcept;

  /**
   * Returns the result of subtracting the two vectors.
   *
   * @param other the other vector to subtract from the first vector.
   * @return the resulting vector of the subtraction.
   * @since 0.1.0
   */
  [[nodiscard]] Vector2 operator-(const Vector2& other) const noexcept;

  /**
   * Returns the dot product of this vector with the supplied vector. This
   * operator is effectively equivalent to the Vector2::Dot method.
   *
   * @param other the other operand of the dot product.
   * @return the dot product of this vector with the supplied vector.
   * @since 0.1.0
   */
  [[nodiscard]] float operator*(const Vector2& other) const noexcept;

  /**
   * Indicates whether or not the two vectors are equal. Two vectors are
   * considered equal if they have the same coordinates.
   *
   * @param other the other vector to compare this vector to.
   * @return true if the vectors have the same coordinates; false otherwise.
   * @since 0.1.0
   */
  [[nodiscard]] bool operator==(const Vector2& other) const noexcept;

  /**
   * Indicates whether or not the two vectors are not equal. Two vectors are not
   * equal if they don't have the same coordinates.
   *
   * @param other the other vector to compare this vector to.
   * @return true if the vectors don't have the same coordinates; false
   * otherwise.
   * @since 0.1.0
   */
  [[nodiscard]] bool operator!=(const Vector2& other) const noexcept;

  /**
   * Returns the dot product of this vector with the supplied vector.
   *
   * @param other the other operand of the dot product.
   * @return the dot product of this vector with the supplied vector.
   * @since 0.1.0
   */
  [[nodiscard]] float dot(const Vector2& other) const noexcept;

  /**
   * Returns the distance between the vector and the supplied vector.
   *
   * @param other the vector to calculate the distance to.
   * @return the distance between the vector and the supplied vector.
   * @since 0.1.0
   */
  [[nodiscard]] float distance_to(const Vector2& other) const noexcept;

  /**
   * Returns the squared distance between the vector and the supplied vector.
   *
   * @param other the vector to calculate the distance to.
   * @return the squared distance between the vector and the supplied vector.
   * @since 0.1.0
   */
  [[nodiscard]] float distance_to_2(const Vector2& other) const noexcept;

  /**
   * Returns the angle between this vector and the supplied vector. The returned
   * value is in degrees. The returned value is always the smallest angle
   * between the two vectors.
   *
   * @param other the other vector to calculate the angle against.
   * @return the angle between this vector and the supplied vector in degrees,
   * in the range [0, 180].
   * @since 0.1.0
   */
  [[nodiscard]] int angle(const Vector2& other) const noexcept;

  /**
   * Returns the integer representation of the x-coordinate of the vector.
   *
   * @return the x-coordinate of the vector.
   * @since 0.1.0
   */
  [[nodiscard]] int get_x() const noexcept
  {
    return Math::round(x);
  }

  /**
   * Returns the the integer representation of the y-coordinate of the vector.
   *
   * @return the y-coordinate of the vector.
   * @since 0.1.0
   */
  [[nodiscard]] int get_y() const noexcept
  {
    return Math::round(y);
  }

  /**
   * Calculates and returns the length of the vector.
   *
   * @return the length of the vector.
   * @since 0.1.0
   */
  [[nodiscard]] float get_length() const noexcept;

  /**
   * Calculates and returns the squared length of the vector. This method is
   * useful when comparing the length of two vectors, where the square roots
   * doesn't have to be computed. This method is slightly faster than the
   * ordinary GetLength method.
   *
   * @return the squared length of the vector.
   * @since 0.1.0
   */
  [[nodiscard]] float get_length_2() const noexcept;

  /**
   * Indicates whether or not the vector is the zero vector.
   *
   * @return true if all coordinates are zero; false otherwise.
   * @since 0.1.0
   */
  [[nodiscard]] bool is_zero() const noexcept;

  /**
   * Indicates whether or not the vector is a unit vector (a vector with length
   * 1).
   *
   * @return true if the vector is a unit vector; false otherwise.
   * @since 0.1.0
   */
  [[nodiscard]] bool is_unit() const noexcept;
};

/**
 * A unit vector with the coordinates (1, 0).
 *
 * @since 0.1.0
 */
static constexpr Vector2 xUnit = Vector2(1, 0);

/**
 * A unit vector with the coordinates (0, 1).
 *
 * @since 0.1.0
 */
static constexpr Vector2 yUnit = Vector2(0, 1);

}  // namespace albinjohansson::wanderer
