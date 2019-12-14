#pragma once
#include <cmath>

namespace albinjohansson::wanderer {

/**
 * The MathUtils class provides utilities related to math.
 *
 * @since 0.1.0
 */
class MathUtils final {
 public:
  MathUtils() = delete;

  ~MathUtils() = default;

  /**
   * Indicates whether or not two doubles are almost equal. The two values are considered equal
   * if the absolute value of their difference is in the range [0, epsilon).
   *
   * @param a the first value.
   * @param b the second value.
   * @param epsilon the epsilon value, set to 0.001 by default.
   * @return true if the values are almost equal; false otherwise.
   * @since 0.1.0
   */
  [[nodiscard]] static constexpr bool AlmostEqual(double a, double b, double epsilon = 0.001) {
    return std::abs(a - b) < epsilon;
  }

  /**
   * Indicates whether or not two floats are almost equal. The two values are considered equal
   * if the absolute value of their difference is in the range [0, epsilon).
   *
   * @param a the first value.
   * @param b the second value.
   * @param epsilon the epsilon value, set to 0.001f by default.
   * @return true if the values are almost equal; false otherwise.
   * @since 0.1.0
   */
  [[nodiscard]] static constexpr bool AlmostEqual(float a, float b, float epsilon = 0.001f) {
    return std::abs(a - b) < epsilon;
  }
};

}
