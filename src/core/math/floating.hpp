#pragma once

#include <cmath>     // abs, round
#include <concepts>  // floating_point

namespace wanderer {

/// \addtogroup core
/// \{

// TODO rune

/// Rounds a floating-point value and returns it as an `int`
template <std::floating_point T>
[[nodiscard]] inline auto round(const T f) noexcept(noexcept(std::round(f))) -> int
{
  return static_cast<int>(std::round(f));
}

/// \} End of group core

}  // namespace wanderer
