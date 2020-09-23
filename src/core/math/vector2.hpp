#pragma once

#include <cmath>  // acos
#include <type_traits>

#include "angles.hpp"
#include "floating.hpp"
#include "index_to_matrix.hpp"

namespace wanderer {

template <typename T>
class basic_vector2 final
{
 public:
  /**
   * @brief Creates a vector with components (0, 0).
   *
   * @since 0.1.0
   */
  constexpr basic_vector2() noexcept = default;

  /**
   * @brief Creates a vector with the specified components.
   *
   * @param x the initial x-coordinate.
   * @param y the initial y-coordinate.
   *
   * @since 0.1.0
   */
  constexpr basic_vector2(T x, T y) noexcept : m_x{x}, m_y{y}
  {}

  /**
   * @brief Sets the x-coordinate of the vector.
   *
   * @param x the new x-coordinate of the vector.
   *
   * @since 0.1.0
   */
  constexpr void set_x(T x) noexcept
  {
    m_x = x;
  }

  /**
   * @brief Sets the y-coordinate of the vector.
   *
   * @param y the new y-coordinate of the vector.
   *
   * @since 0.1.0
   */
  constexpr void set_y(T y) noexcept
  {
    m_y = y;
  }

  /**
   * @brief Scales the components of the vector by the specified amount.
   *
   * @param scale the scale that will be used, may be negative.
   *
   * @since 0.1.0
   */
  constexpr void scale(T scale) noexcept
  {
    m_x *= scale;
    m_y *= scale;
  }

  /**
   * @brief Normalises the vector.
   *
   * @note If the vector is the zero vector, then this function has no effect.
   *
   * @details The vector will have length 1 after this operation, i.e. the
   * vector will become a unit vector.
   *
   * @since 0.1.0
   */
  void norm() noexcept
  {
    if (const auto mag = magnitude(); mag != 0) {
      m_x /= mag;
      m_y /= mag;
    }
  }

  /**
   * @brief Turns the vector into the zero vector.
   *
   * @post the x- and y-coordinates will be equal to `0`.
   *
   * @since 0.1.0
   */
  constexpr void zero() noexcept
  {
    m_x = 0;
    m_y = 0;
  }

  /**
   * @brief Sets the magnitude of the vector.
   *
   * @note If the supplied magnitude is negative, the vector becomes the zero
   * vector.
   *
   * @param mag the new magnitude of the vector.
   *
   * @since 0.1.0
   */
  void set_magnitude(T mag) noexcept
  {
    if (mag <= 0) {
      zero();
      return;
    }

    const auto previousMag = magnitude();
    if (previousMag == 0 || previousMag == mag) {
      return;  // no need to scale
    } else {
      scale(mag / previousMag);
    }
  }

  /**
   * @brief Linearly interpolates this vector.
   *
   * @pre `alpha` must be in the range [0, 1].
   *
   * @param target the target of the interpolation.
   * @param alpha the interpolation coefficient, in the range [0, 1].
   *
   * @since 0.1.0
   */
  constexpr void lerp(const basic_vector2& target, T alpha) noexcept
  {
    const auto invAlpha = T{1} - alpha;
    m_x = (m_x * invAlpha) + (target.m_x * alpha);
    m_y = (m_y * invAlpha) + (target.m_y * alpha);
  }

  /**
   * @brief Interpolates this vector.
   *
   * @pre `alpha` must be in the range [0, 1].
   *
   * @details This function calls `lerp` with an alpha coefficent based on
   * the supplied alpha value.
   *
   * @param target the target vector of the interpolation.
   * @param alpha the interpolation coefficient, in the range [0, 1].
   *
   * @since 0.1.0
   */
  constexpr void lerp_smooth(const basic_vector2& target, T alpha) noexcept
  {
    lerp(target, alpha * alpha * alpha * (alpha * (alpha * 6 - 15) + 10));
  }

  /**
   * @brief Makes the vector point at the supplied vector.
   *
   * @details The vector will maintain its magnitude through this operation.
   *
   * @param target the target vector (or point) that this vector will be made to
   * point at.
   *
   * @since 0.1.0
   */
  void point_at(const basic_vector2<T>& target) noexcept
  {
    point_at(target, magnitude());
  }

  /**
   * @brief Makes the vector point at the supplied vector.
   *
   * @details The other vector is treated as a point in the plane.
   *
   * @note A negative length value will turn the vector into the zero vector.
   *
   * @param target the vector to point this vector at.
   * @param length the length of the invoked vector after the operation.
   *
   * @since 0.1.0
   */
  void point_at(const basic_vector2<T>& target, T length) noexcept
  {
    if (length <= 0) {
      zero();
    } else {
      m_x = target.m_x - m_x;
      m_y = target.m_y - m_y;
      norm();
      scale(length);
    }
  }

  /**
   * @brief Negates the components of the vector.
   *
   * @details A vector with components (20, 30) becomes (-20, -30).
   *
   * @since 0.1.0
   */
  constexpr void negate() noexcept
  {
    m_x = -m_x;
    m_y = -m_y;
  }

  /**
   * @brief Adds the supplied vector to this vector.
   *
   * @param other the vector that will be added to this vector.
   *
   * @since 0.1.0
   */
  constexpr void operator+=(const basic_vector2& other) noexcept
  {
    m_x += other.m_x;
    m_y += other.m_y;
  }

  /**
   * @brief Subtracts the supplied vector to this vector.
   *
   * @param other the vector that will be subtracted from this vector.
   *
   * @since 0.1.0
   */
  constexpr void operator-=(const basic_vector2& other) noexcept
  {
    m_x -= other.m_x;
    m_y -= other.m_y;
  }

  /**
   * @brief Returns the magnitude (length) of this vector.
   *
   * @return the magnitude of this vector.
   *
   * @since 0.1.0
   */
  [[nodiscard]] auto magnitude() const noexcept -> T
  {
    return std::sqrt(m_x * m_x + m_y * m_y);
  }

  /**
   * @brief Returns the squared magnitude of this vector.
   *
   * @return the squared magnitude of this vector.
   *
   * @since 0.1.0
   */
  [[nodiscard]] constexpr auto magnitude2() const noexcept -> T
  {
    return (m_x * m_x) + (m_y * m_y);
  }

  /**
   * @brief Indicates whether or not the vector has zero has both of its
   * components.
   *
   * @return `true` if both of this vectors components are zero; `false`
   * otherwise.
   *
   * @since 0.1.0
   */
  [[nodiscard]] constexpr auto is_zero() const noexcept -> bool
  {
    if constexpr (std::is_integral_v<T>) {
      return m_x == 0 && m_y == 0;
    } else {
      return almost_equal(m_x, 0) && almost_equal(m_y, 0);
    }
  }

  /**
   * @brief Indicates whether or not this vector is a unit vector.
   *
   * @details A unit vector is a vector with length 1.
   *
   * @return `true` if this vector is a unit vector; `false` otherwise.
   *
   * @since 0.1.0
   */
  [[nodiscard]] auto is_unit() const noexcept -> bool
  {
    if constexpr (std::is_integral_v<T>) {
      return magnitude() == 1;
    } else {
      return almost_equal(magnitude(), 1);
    }
  }

  /**
   * @brief Returns the x-coordinate of the vector.
   *
   * @return the x-coordinate of the vector.
   *
   * @since 0.1.0
   */
  [[nodiscard]] constexpr auto x() const noexcept -> T
  {
    return m_x;
  }

  /**
   * @brief Returns the y-coordinate of the vector.
   *
   * @return the y-coordinate of the vector.
   *
   * @since 0.1.0
   */
  [[nodiscard]] constexpr auto y() const noexcept -> T
  {
    return m_y;
  }

 private:
  T m_x{0};
  T m_y{0};
};

/**
 * @brief Returns the sum vector from adding two vectors.
 *
 * @tparam T the representation type used by the vectors.
 *
 * @param lhs the left-hand side vector.
 * @param rhs the right-hand side vector.
 *
 * @return the resulting vector from adding the two vectors.
 *
 * @since 0.1.0
 */
template <typename T>
[[nodiscard]] constexpr auto operator+(const basic_vector2<T>& lhs,
                                       const basic_vector2<T>& rhs) noexcept
    -> basic_vector2<T>
{
  return basic_vector2{lhs.x() + rhs.x(), lhs.y() + rhs.y()};
}

/**
 * @brief Returns the difference vector from subtracting two vectors.
 *
 * @tparam T the representation type used by the vectors.
 *
 * @param lhs the left-hand side vector.
 * @param rhs the right-hand side vector.
 *
 * @return the resulting vector from subtracting the two vectors.
 *
 * @since 0.1.0
 */
template <typename T>
[[nodiscard]] constexpr auto operator-(const basic_vector2<T>& lhs,
                                       const basic_vector2<T>& rhs) noexcept
    -> basic_vector2<T>
{
  return basic_vector2{lhs.x() - rhs.x(), lhs.y() - rhs.y()};
}

/**
 * @brief Returns the result from scaling the supplied vector.
 *
 * @tparam T the representation type used by the vectors.
 *
 * @param vector the vector that will be scaled.
 * @param scalar the amount to scale the vector by.
 *
 * @return a scaled version of the supplied vector.
 *
 * @since 0.1.0
 */
template <typename T>
[[nodiscard]] constexpr auto operator*(const basic_vector2<T>& vector,
                                       T scalar) noexcept -> basic_vector2<T>
{
  return basic_vector2{vector.x() * scalar, vector.y() * scalar};
}

/**
 * @brief Returns the result from scaling the supplied vector.
 *
 * @tparam T the representation type used by the vectors.
 *
 * @param scalar the amount to scale the vector by.
 * @param vector the vector that will be scaled.
 *
 * @return a scaled version of the supplied vector.
 *
 * @since 0.1.0
 */
template <typename T>
[[nodiscard]] constexpr auto operator*(T scalar,
                                       const basic_vector2<T>& vector) noexcept
    -> basic_vector2<T>
{
  return vector * scalar;
}

/**
 * @brief Returns the dot product of two vectors.
 *
 * @note The dot product is commutative, which means that the order of
 * the operands doesn't matter.
 *
 * @tparam T the representation type used by the vectors.
 *
 * @param lhs the left-hand side vector.
 * @param rhs the right-hand side vector.
 *
 * @return the dot product of the two vectors.
 *
 * @since 0.1.0
 */
template <typename T>
[[nodiscard]] constexpr auto operator*(const basic_vector2<T>& lhs,
                                       const basic_vector2<T>& rhs) noexcept
    -> T
{
  return lhs.x() * rhs.x() + lhs.y() * rhs.y();
}

/**
 * @brief Indicates whether or not two vectors are equal.
 *
 * @tparam T the representation type used by the vectors.
 *
 * @param lhs the left-hand side vector.
 * @param rhs the right-hand side vector.
 *
 * @return `true` if the vectors are the same; `false` otherwise.
 *
 * @since 0.1.0
 */
template <typename T>
[[nodiscard]] constexpr auto operator==(const basic_vector2<T>& lhs,
                                        const basic_vector2<T>& rhs) noexcept
    -> bool
{
  return lhs.x() == rhs.x() && lhs.y() == rhs.y();
}

/**
 * @brief Indicates whether or not two vectors aren't equal.
 *
 * @tparam T the representation type used by the vectors.
 *
 * @param lhs the left-hand side vector.
 * @param rhs the right-hand side vector.
 *
 * @return `true` if the vectors aren't the same; `false` otherwise.
 *
 * @since 0.1.0
 */
template <typename T>
[[nodiscard]] constexpr auto operator!=(const basic_vector2<T>& lhs,
                                        const basic_vector2<T>& rhs) noexcept
    -> bool
{
  return !(lhs == rhs);
}

/**
 * @brief Returns the distance between two vectors.
 *
 * @details The vectors are treated as points in the plane.
 *
 * @tparam T the representation type used by the vectors.
 *
 * @param lhs the left-hand side vector.
 * @param rhs the right-hand side vector.
 *
 * @return the distance between the two vectors.
 *
 * @since 0.1.0
 */
template <typename T>
[[nodiscard]] auto distance(const basic_vector2<T>& lhs,
                            const basic_vector2<T>& rhs) noexcept -> T
{
  if (lhs == rhs) {
    return 0;
  } else {
    const auto xDiff = rhs.x() - lhs.x();
    const auto yDiff = rhs.y() - lhs.y();
    return std::sqrt(xDiff * xDiff + yDiff * yDiff);
  }
}

/**
 * @brief Returns the cross product between two vectors.
 *
 * @tparam T the representation type used by the vectors.
 *
 * @param lhs the left-hand side vector.
 * @param rhs the right-hand side vector.
 *
 * @return the cross product of the vectors.
 *
 * @since 0.1.0
 */
template <typename T>
[[nodiscard]] constexpr auto cross(const basic_vector2<T>& lhs,
                                   const basic_vector2<T>& rhs) noexcept -> T
{
  return lhs.x() * rhs.y() - lhs.y() * rhs.x();
}

/**
 * @brief Returns the angle between two vectors.
 *
 * @note This function returns zero if any of the supplied vectors are the
 * zero vector.
 *
 * @tparam T the representation type used by the vectors.
 *
 * @param lhs the left-hand side vector.
 * @param rhs the right-hand side vector.
 *
 * @return the angle between the two vectors.
 *
 * @since 0.1.0
 */
template <typename T>
[[nodiscard]] auto angle(const basic_vector2<T>& lhs,
                         const basic_vector2<T>& rhs) noexcept -> T
{
  if (lhs.is_zero() || rhs.is_zero() || lhs == rhs) {
    return 0;
  }

  const auto mag1 = lhs.magnitude();
  const auto mag2 = rhs.magnitude();

  const auto cos = (lhs * rhs) / mag1 / mag2;
  const auto sin = cross(lhs, rhs) / mag1 / mag2;

  if (const auto angle = std::acos(cos); sin < 0) {
    return -angle;
  } else {
    return angle;
  }
}

using vector2f = basic_vector2<float>;

}  // namespace wanderer
