#pragma once

#include <cmath>  // abs, round

namespace wanderer {

/**
 * \brief Indicates whether or not two floating-point values are almost equal.
 *
 * \details The two values are considered equal if the absolute value of
 * their difference is in the range [0, `epsilon`).
 *
 * \param a the first value.
 * \param b the second value.
 * \param epsilon the epsilon value.
 *
 * \return `true` if the values are almost equal; `false` otherwise.
 *
 * \since 0.1.0
 */
[[nodiscard]] inline auto almost_equal(const double a,
                                       const double b,
                                       const double epsilon = 0.001) -> bool
{
  return std::abs(a - b) < epsilon;
}

/**
 * \copydoc almost_equal(double, double, double)
 */
[[nodiscard]] inline auto almost_equal(const float a,
                                       const float b,
                                       const float epsilon = 0.001f) noexcept -> bool
{
  return std::abs(a - b) < epsilon;
}

[[nodiscard]] inline auto round(const float f) noexcept -> int
{
  return static_cast<int>(std::round(f));
}

}  // namespace wanderer
