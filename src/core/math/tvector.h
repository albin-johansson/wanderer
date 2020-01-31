#pragma once
#include <type_traits>
#include "math_utils.h"

namespace albinjohansson::wanderer::experimental {

template<typename T = float>
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

  constexpr Vector2() noexcept = default;

  constexpr Vector2(const Vector2<T>& other) noexcept : x{other.x}, y{other.y} {}

  Vector2(Vector2<T>&& other) noexcept : x{other.x}, y{other.y} {}

  constexpr Vector2(T x, T y) : x{x}, y{y} {}

  ~Vector2() noexcept = default;

  auto& operator=(const Vector2<T>& other) noexcept {
    if (this != &other) {
      x = other.x;
      y = other.y;
    }
    return *this;
  }

  auto& operator=(Vector2<T>&& other) noexcept {
    x = other.x;
    y = other.y;
    return *this;
  }

  void scale(T scale) noexcept {
    x *= scale;
    y *= scale;
  }

  void norm() noexcept {
    T length = get_length();
    if (length != 0) {
      x /= length;
      y /= length;
    }
  }

  void zero() noexcept {
    x = y = 0;
  }

  void set(const Vector2<T>& other) noexcept {
    x = other.x;
    y = other.y;
  }

  void set(T x, T y) noexcept {
    this->x = x;
    this->y = y;
  }

  void set_length(T length) noexcept {
    if (length == 0) {
      x = 0;
      y = 0;
      return;
    }

    T prev = get_length();
    if (prev == 0 || prev == length) {
      return;
    }
    scale(length / prev);
  }

  void lerp(const Vector2<T>& target, T alpha) noexcept {
    T invAlpha = 1 - alpha;
    this->x = (x * invAlpha) + (target.x * alpha);
    this->y = (y * invAlpha) + (target.y * alpha);
  }

  void interpolate(const Vector2<T>& target, float alpha) noexcept {
    lerp(target, alpha * alpha * alpha * (alpha * (alpha * 6 - 15) + 10));
  }

  void add(const Vector2<T>& other) noexcept {
    x += other.x;
    y += other.y;
  }

  void add(T x, T y) noexcept {
    this->x += x;
    this->y += y;
  }

  void sub(const Vector2<T>& other) noexcept {
    x -= other.x;
    y -= other.y;
  }

  void sub(T x, T y) noexcept {
    this->x -= x;
    this->y -= y;
  }

  void look_at(const Vector2<T>& target) noexcept {
    look_at(target, get_length());
  }

  void look_at(const Vector2<T>& target, T length) noexcept {
    if (length <= 0) {
      x = 0;
      y = 0;
    } else {
      x = (target.x - x);
      y = (target.y - y);
      norm();
      scale(length);
    }
  }

  void invert() noexcept {
    x *= -1;
    y *= -1;
  }

  [[nodiscard]]
  auto operator+(const Vector2<T>& other) const noexcept {
    return Vector2<T>{x + other.x, y + other.y};
  }

  [[nodiscard]]
  auto operator-(const Vector2<T>& other) const noexcept {
    return Vector2<T>{x - other.x, y - other.y};
  }

  [[nodiscard]]
  T operator*(const Vector2<T>& other) const noexcept {
    return dot(other);
  }

  [[nodiscard]]
  bool operator==(const Vector2<T>& other) const noexcept {
    if constexpr (std::is_integral_v<T>) {
      return (x == other.x) && (y == other.y);
    } else {
      return MathUtils::almost_equal(x, other.x)
          && MathUtils::almost_equal(y, other.y);
    }
  }

  [[nodiscard]]
  bool operator!=(const Vector2<T>& other) const noexcept {
    return !(*this == other);
  }

  [[nodiscard]]
  T dot(const Vector2<T>& other) const noexcept {
    return (x * other.x) + (y * other.y);
  }

  [[nodiscard]]
  T distance_to(const Vector2<T>& other) const noexcept {
    const auto xDiff = other.x - x;
    const auto yDiff = other.y - y;
    return std::sqrt((xDiff * xDiff) + (yDiff * yDiff));
  }

  [[nodiscard]]
  T distance_to_2(const Vector2<T>& other) const noexcept {
    const auto xDiff = other.x - x;
    const auto yDiff = other.y - y;
    return (xDiff * xDiff) + (yDiff * yDiff);
  }

  [[nodiscard]]
  int angle(const Vector2<T>& other) const noexcept {
    return MathUtils::round(MathUtils::to_degrees(std::acos(dot(other))));
  }

  [[nodiscard]]
  T get_length() const noexcept {
    return std::sqrt((x * x) + (y * y));
  }

  [[nodiscard]]
  T get_length_2() const noexcept {
    return (x * x) + (y * y);
  }

  [[nodiscard]]
  bool is_zero() const noexcept {
    if constexpr (std::is_integral_v<T>) {
      return x == 0 && y == 0;
    } else {
      return MathUtils::almost_equal(x, 0)
          && MathUtils::almost_equal(y, 0);
    }
  }

  [[nodiscard]]
  bool is_unit() const noexcept {
    if constexpr (std::is_integral_v<T>) {
      return get_length() == 1;
    } else {
      return MathUtils::almost_equal(get_length(), 1);
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

using Vector2f = Vector2<float>;
using Vector2d = Vector2<double>;
using Vector2i = Vector2<int>;

}
