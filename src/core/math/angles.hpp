#pragma once

#include <numbers>  // pi_v

namespace wanderer {

inline constexpr auto pi = std::numbers::pi_v<float>;

[[nodiscard]] inline constexpr auto to_degrees(const float radians) noexcept -> float
{
  return (radians * 180.0f) / pi;
}

[[nodiscard]] inline constexpr auto to_radians(const float degrees) noexcept -> float
{
  return (degrees * pi) / 180.0f;
}

}  // namespace wanderer
