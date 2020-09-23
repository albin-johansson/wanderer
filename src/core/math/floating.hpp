#pragma once

#include <cmath>  // abs, round

namespace wanderer {

/**
 * @brief Indicates whether or not two floating-point values are almost equal.
 *
 * @details The two values are considered equal if the absolute value of
 * their difference is in the range [0, `epsilon`).
 *
 * @param a the first value.
 * @param b the second value.
 * @param epsilon the epsilon value.
 *
 * @return `true` if the values are almost equal; `false` otherwise.
 *
 * @since 0.1.0
 */
[[nodiscard]] inline auto almost_equal(double a,
                                       double b,
                                       double epsilon = 0.001) noexcept -> bool
{
  return std::abs(a - b) < epsilon;
}

/**
 * @copydoc almost_equal(double, double, double)
 */
[[nodiscard]] inline auto almost_equal(float a,
                                       float b,
                                       float epsilon = 0.001f) noexcept -> bool
{
  return std::abs(a - b) < epsilon;
}

[[nodiscard]] inline auto round(float f) noexcept -> int
{
  return static_cast<int>(std::round(f));
}

}  // namespace wanderer
