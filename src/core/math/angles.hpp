#pragma once

namespace wanderer {

template <typename T>
inline constexpr T pi{static_cast<T>(3.14159265358979323)};

[[nodiscard]] inline constexpr auto to_degrees(float radians) noexcept -> float
{
  return (radians * 180.0f) / pi<float>;
}

[[nodiscard]] inline constexpr auto to_degrees(double radians) noexcept
    -> double
{
  return (radians * 180.0) / pi<double>;
}

[[nodiscard]] inline constexpr auto to_radians(float degrees) noexcept -> float
{
  return (degrees * pi<float>) / 180.0f;
}

[[nodiscard]] inline constexpr auto to_radians(double degrees) noexcept
    -> double
{
  return (degrees * pi<double>) / 180.0;
}

}  // namespace wanderer
