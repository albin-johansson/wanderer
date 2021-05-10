#pragma once

#include <cmath>  // abs, round

namespace wanderer {

/// \addtogroup core
/// \{

// TODO rune

/// Rounds a `float` and returns it as an `int`
[[nodiscard]] inline auto round(const float f) noexcept(noexcept(std::round(f))) -> int
{
  return static_cast<int>(std::round(f));
}

/// \} End of group core

}  // namespace wanderer
