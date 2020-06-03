#pragma once
#include <cmath>
#include <utility>

namespace wanderer {

template <typename T>
inline constexpr T pi{static_cast<T>(3.14159265358979323)};

inline constexpr auto pi_f = pi<float>;
inline constexpr auto pi_d = pi<double>;

class Math final {
 public:
  Math() = delete;

  ~Math() = default;

  [[nodiscard]] static constexpr float to_degrees(float radians) noexcept
  {
    return (radians * 180.0f) / pi_f;
  }

  [[nodiscard]] static constexpr double to_degrees(double radians) noexcept
  {
    return (radians * 180.0) / pi_d;
  }

  [[nodiscard]] static constexpr float to_radians(float degrees) noexcept
  {
    return (degrees * pi_f) / 180.0f;
  }

  [[nodiscard]] static constexpr double to_radians(double degrees) noexcept
  {
    return (degrees * pi_d) / 180.0;
  }

  [[nodiscard]] static constexpr int round(float f) noexcept
  {
    return static_cast<int>(std::round(f));
  }

  /**
   * Calculates and returns the matrix position from an index and the amount of
   * columns in the matrix.
   *
   * @param index the index that will be converted.
   * @param nCols the number of columns in the matrix, can't be zero.
   * @return a pair of values that represent the matrix position in the format
   * (row, col).
   * @since 0.1.0
   */
  [[nodiscard]] static constexpr std::pair<int, int> index_to_matrix_pos(
      int index,
      int nCols) noexcept
  {
    return {index / nCols, index % nCols};
  }

  /**
   * Indicates whether or not two doubles are almost equal. The two values are
   * considered equal if the absolute value of their difference is in the range
   * [0, epsilon).
   *
   * @param a the first value.
   * @param b the second value.
   * @param epsilon the epsilon value, set to 0.001 by default.
   * @return true if the values are almost equal; false otherwise.
   * @since 0.1.0
   */
  [[nodiscard]] static constexpr bool
  almost_equal(double a, double b, double epsilon = 0.001) noexcept
  {
    return std::abs(a - b) < epsilon;
  }

  /**
   * Indicates whether or not two floats are almost equal. The two values are
   * considered equal if the absolute value of their difference is in the range
   * [0, epsilon).
   *
   * @param a the first value.
   * @param b the second value.
   * @param epsilon the epsilon value, set to 0.001f by default.
   * @return true if the values are almost equal; false otherwise.
   * @since 0.1.0
   */
  [[nodiscard]] static constexpr bool
  almost_equal(float a, float b, float epsilon = 0.001f) noexcept
  {
    return std::abs(a - b) < epsilon;
  }
};

}  // namespace wanderer