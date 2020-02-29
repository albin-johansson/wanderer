#pragma once
#include <type_traits>

#include "math.h"

namespace albinjohansson::wanderer::experimental {

/**
 * The Vector2 class represents a two-dimensional vector (in the plane). The
 * vector supports all kinds of numerical components. There are a couple of type
 * aliases available for this class, with the format Vector2x, where x is the
 * initial letter of the internal type (e.g, Vector2f for a float-based vector).
 *
 * @tparam T the type of the components of the vector. Must be a numerical type
 * (i.e. an integral or floating-point type). By default, the type is set to
 * float.
 * @since 0.1.0
 */
template <typename T = float>
class Vector2 final {
 public:
  static_assert(std::is_integral_v<T> || std::is_floating_point_v<T>,
                "Vector2 requires a numerical type!");
  static_assert(!std::is_pointer_v<T>,
                "Vector2 requires non-pointer template parameter!");
  static_assert(std::is_scalar_v<T>);
  static_assert(std::is_trivial_v<T>,
                "Vector2 requires a trivial template parameter!");

  T x = 0;
  T y = 0;

  /**
   * Default constructor. Creates a vector with the components (0, 0).
   *
   * @since 0.1.0
   */
  constexpr Vector2() noexcept = default;

  /**
   * Copy constructor.
   *
   * @param other the vector that will be copied.
   * @since 0.1.0
   */
  constexpr Vector2(const Vector2<T>& other) noexcept : x{other.x}, y{other.y}
  {}

  /**
   * Move constructor.
   *
   * @param other the constructor that will be moved.
   * @since 0.1.0
   */
  Vector2(Vector2<T>&& other) noexcept : x{other.x}, y{other.y}
  {}

  /**
   * Creates a vector with the specified components.
   *
   * @param x the x-coordinate that will be used by the vector.
   * @param y the y-coordinate that will be used by the vector.
   * @since 0.1.0
   */
  constexpr Vector2(T x, T y) noexcept : x{x}, y{y}
  {}

  /**
   * @since 0.1.0
   */
  ~Vector2() noexcept = default;

  /**
   * Copies the components of the supplied vector.
   *
   * @param other the vector that will be copied.
   * @return auto& a reference to the vector that was assigned.
   * @since 0.1.0
   */
  auto& operator=(const Vector2<T>& other) noexcept
  {
    if (this != &other) {
      x = other.x;
      y = other.y;
    }
    return *this;
  }

  /**
   * Moves the components of the supplied vector into this vector.
   *
   * @param other the vector that will be moved.
   * @return auto& a reference to the vector that was assigned.
   * @since 0.1.0
   */
  auto& operator=(Vector2<T>&& other) noexcept
  {
    x = other.x;
    y = other.y;
    return *this;
  }

  /**
   * Scales the components of the vector by the specified amount.
   *
   * @param scale the scale that will be used, may be negative.
   * @since 0.1.0
   */
  void scale(T scale) noexcept
  {
    x *= scale;
    y *= scale;
  }

  /**
   * Normalises the vector. The vector will have length 1 after this operation
   * (the vector will become a unit vector).
   *
   * @since 0.1.0
   */
  void norm() noexcept
  {
    if constexpr (std::is_floating_point_v<T>) {
      const auto magnitude = get_magnitude();
      if (magnitude != 0) {
        x /= magnitude;
        y /= magnitude;
      }
    } else {
      const auto magnitude = static_cast<float>(get_magnitude());
      if (magnitude != 0) {
        const auto fx = static_cast<float>(x) / magnitude;
        const auto fy = static_cast<float>(y) / magnitude;
        x = Math::round(fx);
        y = Math::round(fy);
      }
    }
  }

  /**
   * Sets both of the components of the vector to zero.
   *
   * @since 0.1.0
   */
  void zero() noexcept
  {
    x = y = 0;
  }

  /**
   * Copies the fields of the supplied vector into this vector.
   *
   * @param other the vector that holds the components that will be copied.
   * @since 0.1.0
   */
  void set(const Vector2<T>& other) noexcept
  {
    x = other.x;
    y = other.y;
  }

  /**
   * Sets the components of the vector.
   *
   * @param newX the new x-coordinate of the vector.
   * @param newY the new y-coordinate of the vector.
   * @since 0.1.0
   */
  void set(T newX, T newY) noexcept
  {
    x = newX;
    y = newY;
  }

  /**
   * Sets the magnitude (length) of the vector.
   *
   * @param magnitude the new magnitude of the vector.
   * @since 0.1.0
   */
  void set_magnitude(T magnitude) noexcept
  {
    if (magnitude == 0) {
      x = 0;
      y = 0;
      return;
    }

    const auto oldMagnitude = get_magnitude();
    if (oldMagnitude == 0 || oldMagnitude == magnitude) {
      return;
    }
    scale(magnitude / oldMagnitude);
  }

  /**
   * Performs a linear interpolation on this vector. The supplied alpha value
   * needs to be in the range [0, 1]. If not, unexpected behaviour might occur.
   *
   * @param target the target vector of the interpolation.
   * @param alpha the interpolation coefficient, in the range [0, 1]. The value
   * is NOT checked to be in the expected range.
   * @since 0.1.0
   */
  void interpolate(const Vector2<T>& target, T alpha) noexcept
  {
    const T invAlpha = 1 - alpha;
    this->x = (x * invAlpha) + (target.x * alpha);
    this->y = (y * invAlpha) + (target.y * alpha);
  }

  /**
   * Interpolates this vector. Internally, this method calls the lerp-method
   * with a processed version of the supplied alpha value.
   *
   * @param target the target vector of the interpolation.
   * @param alpha the interpolation coefficient, in the range [0, 1]. The value
   * is NOT checked to be in the expected range.
   * @since 0.1.0
   */
  void interpolate_smooth(const Vector2<T>& target, float alpha) noexcept
  {
    lerp(target, alpha * alpha * alpha * (alpha * (alpha * 6 - 15) + 10));
  }

  /**
   * Adds this vector with the supplied vector. The result is stored in this
   * vector (the invoked vector).
   *
   * @param other the other vector that represents the second operand.
   * @since 0.1.0
   */
  void add(const Vector2<T>& other) noexcept
  {
    x += other.x;
    y += other.y;
  }

  /**
   * Adds this vector with the supplied vector components.
   *
   * @param vx the x-coordinate of the second vector operand.
   * @param vy the y-coordinate of the second vector operand.
   * @since 0.1.0
   */
  void add(T vx, T vy) noexcept
  {
    x += vx;
    y += vy;
  }

  /**
   * Subtracts the supplied vector from this vector. The result is stored in
   * this vector (the invoked vector). In other words, the invoked vector
   * represents the left-hand side operand, and vice versa.
   *
   * @param other the vector to subtract from this vector.
   * @since 0.1.0
   */
  void sub(const Vector2<T>& other) noexcept
  {
    x -= other.x;
    y -= other.y;
  }

  /**
   * Subtracts the supplied vector components from this vector. This vector
   * represents the left-hand side operand.
   *
   * @param vx the x-coordinate of the right-hand side vector operand.
   * @param vy the y-coordinate of the right-hand side vector operand.
   * @since 0.1.0
   */
  void sub(T vx, T vy) noexcept
  {
    x -= vx;
    y -= vy;
  }

  /**
   * Makes this vector "look" at the specified vector (think of the other vector
   * as a point in the plane). The invoked vector will keep its magnitude after
   * this operation.
   *
   * @param target the target vector (or point) that this vector will be made to
   * "look" at.
   * @since 0.1.0
   */
  void look_at(const Vector2<T>& target) noexcept
  {
    look_at(target, get_magnitude());
  }

  /**
   * Makes this vector "look" at the specified vector (think of the other vector
   * as a point in the plane).
   *
   * @param target the target vector (or point) that this vector will be made to
   * "look" at.
   * @param length the length of the invoked vector after the look operation. A
   * non-positive value will cause the invoked vector to have its components set
   * to zero.
   * @since 0.1.0
   */
  void look_at(const Vector2<T>& target, T length) noexcept
  {
    if (length <= 0) {
      x = 0;
      y = 0;
    } else {
      x = target.x - x;
      y = target.y - y;
      norm();
      scale(length);
    }
  }

  /**
   * Negates the components of the vector.
   *
   * @since 0.1.0
   */
  void negate() noexcept
  {
    x = -x;
    y = -y;
  }

  /**
   * Performs a vector addition of the two supplied vectors and returns the
   * result.
   *
   * @param lhs the left-hand side vector.
   * @param rhs the right hand side vector.
   * @return the result of the vector addition of the two supplied vectors.
   * @since 0.1.0
   */
  friend Vector2<T> operator+(const Vector2<T>& lhs,
                              const Vector2<T>& rhs) noexcept
  {
    return {lhs.x + rhs.x, lhs.y + rhs.y};
  }

  /**
   * Performs a vector subtraction of the two supplied vectors and returns the
   * result.
   *
   * @param lhs the left-hand side vector.
   * @param rhs the right hand side vector.
   * @return the result of the vector subtraction of the two supplied vectors.
   * @since 0.1.0
   */
  friend Vector2<T> operator-(const Vector2<T>& lhs,
                              const Vector2<T>& rhs) noexcept
  {
    return {lhs.x - rhs.x, lhs.y - rhs.y};
  }

  /**
   * Calculates and returns the dot product of the two supplied vectors. Note,
   * the dot product is commutative, which means that the order of the operands
   * doesn't matter.
   *
   * @param lhs the left-hand side vector.
   * @param rhs the right-hand side vector.
   * @return the dot product of the two supplied vectors.
   * @since 0.1.0
   */
  friend T operator*(const Vector2<T>& lhs, const Vector2<T>& rhs) noexcept
  {
    return lhs.dot(rhs);
  }

  /**
   * Indicates whether or not two vectors are the same.
   *
   * @param lhs the left-hand side vector.
   * @param rhs the right-hand side vector.
   * @return true if the vectors are the same; false otherwise.
   * @since 0.1.0
   */
  friend bool operator==(const Vector2<T>& lhs, const Vector2<T>& rhs) noexcept
  {
    if constexpr (std::is_integral_v<T>) {
      return (lhs.x == rhs.x) && (lhs.y == rhs.y);
    } else {
      return Math::almost_equal(lhs.x, rhs.x) &&
             Math::almost_equal(lhs.y, rhs.y);
    }
  }

  /**
   * Indicates whether or not two vectors aren't the same.
   *
   * @param lhs the left-hand side vector.
   * @param rhs the right-hand side vector.
   * @return true if the vectors aren't the same; false otherwise.
   * @since 0.1.0
   */
  friend bool operator!=(const Vector2<T>& lhs, const Vector2<T>& rhs) noexcept
  {
    return !(lhs == rhs);
  }

  /**
   * Computes and returns the dot product of this vector and the supplied
   * vector. Note, the dot product is commutative, which means that the order of
   * the operands doesn't matter.
   *
   * @param other the other vector operand.
   * @return the dot product of this vector and the supplied vector.
   * @since 0.1.0
   */
  [[nodiscard]] T dot(const Vector2<T>& other) const noexcept
  {
    return (x * other.x) + (y * other.y);
  }

  /**
   * Returns the distance from this vector to the supplied vector, with the
   * vectors treated as points in the plane.
   *
   * @param other the target vector.
   * @return the distance from this vector to the supplied vector.
   * @since 0.1.0
   */
  [[nodiscard]] T distance_to(const Vector2<T>& other) const noexcept
  {
    const auto xDiff = other.x - x;
    const auto yDiff = other.y - y;
    return std::sqrt((xDiff * xDiff) + (yDiff * yDiff));
  }

  /**
   * Returns the squared distance from this vector to the supplied vector, with
   * the vectors treated as points in the plane.
   *
   * @param other the target vector.
   * @return the squared distance from this vector to the supplied vector.
   * @since 0.1.0
   */
  [[nodiscard]] T distance_to_2(const Vector2<T>& other) const noexcept
  {
    const auto xDiff = other.x - x;
    const auto yDiff = other.y - y;
    return (xDiff * xDiff) + (yDiff * yDiff);
  }

  /**
   * Calculates and returns the angle between this vector and the supplied
   * vector.
   *
   * @param other the other vector that will be used.
   * @return the angle between this vector and the supplied vector.
   * @since 0.1.0
   */
  [[nodiscard]] int angle(const Vector2<T>& other) const noexcept
  {
    return Math::round(Math::to_degrees(std::acos(dot(other))));
  }

  /**
   * Returns the magnitude (length) of this vector.
   *
   * @return the magnitude of this vector.
   * @since 0.1.0
   */
  [[nodiscard]] T get_magnitude() const noexcept
  {
    if constexpr (std::is_floating_point_v<T>) {
      return std::sqrt((x * x) + (y * y));
    } else {
      const auto fx = static_cast<float>(x);
      const auto fy = static_cast<float>(y);
      const auto magnitude = std::sqrt((fx * fx) + (fy * fy));
      return Math::round(magnitude);
    }
  }

  /**
   * Returns the squared magnitude of this vector.
   *
   * @return the squared magnitude of this vector.
   * @since 0.1.0
   */
  [[nodiscard]] T get_magnitude_2() const noexcept
  {
    return (x * x) + (y * y);
  }

  /**
   * Indicates whether or not the vector has zero has both of its components.
   *
   * @return true if both of this vectors components are zero; false otherwise.
   * @since 0.1.0
   */
  [[nodiscard]] constexpr bool is_zero() const noexcept
  {
    if constexpr (std::is_integral_v<T>) {
      return x == 0 && y == 0;
    } else {
      return Math::almost_equal(x, 0) && Math::almost_equal(y, 0);
    }
  }

  /**
   * Indicates whether or not this vector is a unit vector. A unit vector is a
   * vector with length 1.
   *
   * @return true if this vector is a unit vector; false otherwise.
   * @since 0.1.0
   */
  [[nodiscard]] bool is_unit() const noexcept
  {
    if constexpr (std::is_integral_v<T>) {
      return get_magnitude() == 1;
    } else {
      return Math::almost_equal(get_magnitude(), 1);
    }
  }
};

static_assert(std::is_nothrow_default_constructible_v<Vector2<>>);
static_assert(std::is_nothrow_destructible_v<Vector2<>>);

static_assert(std::is_nothrow_copy_constructible_v<Vector2<>>);
static_assert(std::is_nothrow_copy_assignable_v<Vector2<>>);

static_assert(std::is_nothrow_move_constructible_v<Vector2<>>);
static_assert(std::is_nothrow_move_assignable_v<Vector2<>>);

static_assert(std::is_final_v<Vector2<>>);

/**
 * A type alias that is equivalent to Vector2&lt;float&gt;.
 *
 * @since 0.1.0
 */
using Vector2f = Vector2<float>;

/**
 * A type alias that is equivalent to Vector2&lt;double&gt;.
 *
 * @since 0.1.0
 */
using Vector2d = Vector2<double>;

/**
 * A type alias that is equivalent to Vector2&lt;int&gt;.
 *
 * @since 0.1.0
 */
using Vector2i = Vector2<int>;

}  // namespace albinjohansson::wanderer::experimental